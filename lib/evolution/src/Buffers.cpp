#include "Buffers.hpp"
#include "Projection.hpp"
#include "ProgramSelector.hpp"
#include "Camera.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <stdexcept>

namespace
{
  uint32_t bufferDataUsageToGlType(const evolution::BufferDataUsage usage)
  {
    switch (usage)
    {
    case (evolution::BufferDataUsage::StaticDraw):
      return GL_STATIC_DRAW;
      break;
    case (evolution::BufferDataUsage::StaticRead):
      return GL_STATIC_READ;
      break;
    case (evolution::BufferDataUsage::DynamicDraw):
      return GL_DYNAMIC_DRAW;
      break;
    case (evolution::BufferDataUsage::DynamicRead):
      return GL_DYNAMIC_READ;
      break;
      // TODO: support the rest
    }
    return 0;
  }

  // creates a buffer. assumes a vertex array buffer is already bound.
  uint32_t createBuffer(uint32_t type,
                        const void* data,
                        const size_t size,
                        const uint32_t attribIndex,
                        const evolution::BufferDataUsage usage)
  {
    // create and fill a vertex buffer with position data
    uint32_t buffId = 0;
    glGenBuffers(1, &buffId);
    if (!buffId)
      throw std::runtime_error("buffer generation failed");
    glBindBuffer(type, buffId);
    glBufferData(type, size, data, bufferDataUsageToGlType(usage));
    // TODO: use a custom enum instead of this opengl macro garbage
    if (type == GL_ARRAY_BUFFER)
    {
      glVertexAttribPointer(attribIndex, 4, GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(attribIndex);
    }
    return buffId;
  }

} // namespace

namespace evolution
{
  Mesh::Mesh(const PositionBuffer& positions,
             const ColorBuffer& colors,
             IndexBuffer& indices,
             const PositionInfo posInfo,
             ProgramSelector* programSelector,
             const BufferDataUsage usage)
    : m_position(posInfo),
      m_programSelector(programSelector),
      m_currProgram("default")
  {
    if (!programSelector)
      throw std::runtime_error("program selector must be non-null");

    if (indices.size() == 0) // no index buffer
    {
      // generate a default one
      for (uint32_t i = 0; i < positions.size(); i++)
      {
        indices.push_back(i);
      }
    }

    // all vectors need to have the same number of elements
    if (positions.size() != colors.size())
    {
      throw std::runtime_error(
        "invalid mesh setup, buffer count not consistent");
    }

    m_numUniqueVertices = positions.size();
    m_numVertices = indices.size();
    // create and bind the vertex array object
    glGenVertexArrays(1, &m_vaoId);
    if (!m_vaoId)
      throw std::runtime_error("vertex object array creation failed");
    glBindVertexArray(m_vaoId);

    m_posBufferId = createBuffer(GL_ARRAY_BUFFER,
                                 positions.data(),
                                 positions.size() * sizeof(Float4),
                                 0,
                                 usage);
    m_colBufferId = createBuffer(
      GL_ARRAY_BUFFER, colors.data(), colors.size() * sizeof(Float4), 1, usage);
    m_indexBufferId = createBuffer(GL_ELEMENT_ARRAY_BUFFER,
                                   indices.data(),
                                   indices.size() * sizeof(uint32_t),
                                   0,
                                   usage);
  }

  void Mesh::useShader(const std::string& shader)
  {
    m_currProgram = shader;
  }

  void Mesh::setPosition(Float3 newPos)
  {
    m_position.position = newPos;
  }

  void Mesh::movePostion(Float3 delta)
  {
    m_position.position.x += delta.x;
    m_position.position.y += delta.y;
    m_position.position.z += delta.z;
  }

  void Mesh::setRotation(Float3 rotation)
  {
    m_position.rotation = rotation;
  }

  void Mesh::rotate(Float3 delta)
  {
    m_position.rotation.x += delta.x;
    m_position.rotation.y += delta.y;
    m_position.rotation.z += delta.z;
  }

  Float3 Mesh::getPostion()
  {
    return m_position.position;
  }

  Float3 Mesh::getRotation()
  {
    return m_position.rotation;
  }

  Mat4 Mesh::getWorldSpaceTransformation()
  {
    auto mat = identityMatrix();

    rotateAroundX(mat, m_position.rotation.x);
    rotateAroundY(mat, m_position.rotation.y);
    rotateAroundZ(mat, m_position.rotation.z);
    // TODO: add scaling

    translateMatrix(
      mat, m_position.position.x, m_position.position.y, m_position.position.z);
    return mat;
  }

  Mesh::~Mesh()
  {
    release();
  }

  Mesh::Mesh(Mesh&& other)
    : m_colBufferId(other.m_colBufferId),
      m_posBufferId(other.m_posBufferId),
      m_currProgram(other.m_currProgram),
      m_indexBufferId(other.m_indexBufferId),
      m_vaoId(other.m_vaoId),
      m_programSelector(other.m_programSelector),
      m_numUniqueVertices(other.m_numUniqueVertices),
      m_numVertices(other.m_numVertices),
      m_position(other.m_position)
  {
    other.m_colBufferId = 0;
    other.m_indexBufferId = 0;
    other.m_posBufferId = 0;
    other.m_vaoId = 0;
    other.m_programSelector = nullptr;
  }

  Mesh& Mesh::operator=(Mesh&& other)
  {
    if (this != &other)
    {
      release();
      std::swap(m_colBufferId, other.m_colBufferId);
      std::swap(m_posBufferId, other.m_posBufferId);
      std::swap(m_currProgram, other.m_currProgram);
      std::swap(m_indexBufferId, other.m_indexBufferId);
      std::swap(m_vaoId, other.m_vaoId);
      std::swap(m_programSelector, other.m_programSelector);
      std::swap(m_numUniqueVertices, other.m_numUniqueVertices);
      std::swap(m_numVertices, other.m_numVertices);
      std::swap(m_position, other.m_position);
    }
    return other;
  }

  void Mesh::draw(const Camera& camera)
  {
    auto pProgram = m_programSelector->getProgram(m_currProgram);
    auto im = getWorldSpaceTransformation();
    pProgram->addUniform(&im.m[0], 16, "un_modelMatrix");
    auto eyeMatrix = camera.getEyeSpaceMatrix();
    pProgram->addUniform(&eyeMatrix.m[0], 16, "un_eyeMatrix");
    auto projectionMatrix = getProjectionMatrix(
      90.f, 1280.f / 720.f, 0.f, 100.f); // TODO: pass this from somewhere else
    pProgram->addUniform(&projectionMatrix.m[0], 16, "un_projMatrix");
    glBindVertexArray(m_vaoId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    pProgram->bind();
    glDrawElements(GL_TRIANGLES, (GLsizei)m_numVertices, GL_UNSIGNED_INT, 0);
    pProgram->unbind();
    glBindVertexArray(0);
  }

  void Mesh::release()
  {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vaoId);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_posBufferId);
    glDeleteBuffers(1, &m_colBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_indexBufferId);
  }

  Mesh createCubeMesh(ProgramSelector* programSelector)
  {
    PositionBuffer vertices = {
      {-.5f, -.5f, .5f, 1.f},
      {-.5f, .5f, .5f, 1.f},
      {.5f, .5f, .5f, 1.f},
      {.5f, -.5f, .5f, 1.f},
      {-.5f, -.5f, -.5f, 1.f},
      {-.5f, .5f, -.5f, 1.f},
      {.5f, .5f, -.5f, 1.f},
      {.5f, -.5f, -.5f, 1.f},
    };

    ColorBuffer colors = {
      {0.f, 0.f, 1.f, 1.f},
      {1.f, 0.f, 0.f, 1.f},
      {0.f, 1.f, 0.f, 1.f},
      {1.f, 1.f, 0.f, 1.f},
      {1.f, 1.f, 1.f, 1.f},
      {1.f, 0.f, 0.f, 1.f},
      {1.f, 0.f, 1.f, 1.f},
      {0.f, 0.f, 1.f, 1.f},
    };
    IndexBuffer indexBuffer = {0, 2, 1, 0, 3, 2, 4, 3, 0, 4, 7, 3,
                               4, 1, 5, 4, 0, 1, 3, 6, 2, 3, 7, 6,
                               1, 6, 5, 1, 2, 6, 7, 5, 6, 7, 4, 5};
    auto mesh = Mesh(vertices,
                     colors,
                     indexBuffer,
                     evolution::PositionInfo(),
                     programSelector);
    return mesh;
  }
} // namespace evolution
