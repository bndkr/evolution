#include "Buffers.hpp"
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
    if (!buffId) throw std::runtime_error("buffer generation failed");
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
             const BufferDataUsage usage)
  {
    if (indices.size() == 0) // no index buffer
    {
      // generate a default one
      for (uint32_t i = 0; i < positions.size(); i++)
      {
        indices.push_back(i);
      }
    }

    // all vectors need to have the same number of elements
    if (positions.size() != colors.size() || colors.size() != indices.size())
    {
      throw std::runtime_error(
        "invalid mesh setup, buffer count not consistent");
    }

    m_numVertices = positions.size();

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

  Mesh::~Mesh()
  {
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_posBufferId);
    glDeleteBuffers(1, &m_colBufferId);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_indexBufferId);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vaoId);
  }

  void Mesh::draw()
  {
    glBindVertexArray(m_vaoId);
    glDrawElements(GL_TRIANGLES, (GLsizei) m_numVertices, GL_UNSIGNED_INT, 0);
  }
} // namespace evolution
