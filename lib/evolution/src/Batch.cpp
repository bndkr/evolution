#include "Batch.hpp"

#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <stdexcept>

namespace evolution
{
  Batch::Batch(const MeshBuffers& buffers,
               const std::vector<BatchObject>& objects)
  {
    auto indices = buffers.indices;
    auto textureCoods = buffers.texture;
    auto colors = buffers.colors;
    if (indices.size() == 0) // no index buffer
    {
      // generate a default one
      for (uint32_t i = 0; i < buffers.positions.size(); i++)
      {
        indices.push_back(i);
      }
    }

    if (textureCoods.size() == 0) // no texture coords buffer
    {
      // generate a default one
      for (uint32_t i = 0; i < buffers.positions.size(); i++)
      {
        textureCoods.push_back(Float2{});
      }
    }

    if (colors.size() == 0) // no colors
    {
      for (uint32_t i = 0; i < buffers.positions.size(); i++)
      {
        colors.push_back(Float4{});
      }
    }

    if (colors.size() == 1) // use this color for the entire object
    {
      auto solidColor = colors[0];
      colors.clear();
      for (uint32_t i = 0; i < buffers.positions.size(); i++)
      {
        colors.push_back(solidColor);
      }
    }

    // all vectors need to have the same number of elements
    if (buffers.positions.size() != colors.size() ||
        textureCoods.size() != buffers.positions.size())
    {
      throw std::runtime_error(
        "invalid mesh setup, buffer count not consistent");
    }

    m_numUniqueVertices = buffers.positions.size();
    m_numVertices = indices.size();

    std::vector<Vertex> vertices;
    for (size_t i = 0; i < m_numUniqueVertices; i++)
    {
      vertices.push_back(Vertex{
        buffers.positions[i], colors[i], textureCoods[i], buffers.normals[i]});
    }

    // create and bind the vertex array object
    glGenVertexArrays(1, &m_vaoId);
    if (!m_vaoId)
      throw std::runtime_error("vertex object array creation failed");
    glBindVertexArray(m_vaoId);

    glGenBuffers(1, &m_posBufferId);
    glGenBuffers(1, &m_indexBufferId);

    glBindBuffer(GL_ARRAY_BUFFER, m_posBufferId);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vertex) * vertices.size(),
                 vertices.data(),
                 GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(uint32_t) * indices.size(),
                 indices.data(),
                 GL_DYNAMIC_DRAW);

    size_t vertexSize = 12 * sizeof(float);

    // position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(
      1, 4, GL_FLOAT, GL_FALSE, vertexSize, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coords
    glVertexAttribPointer(
      2, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);
    // normals
    glVertexAttribPointer(
      3, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }
} // namespace evolution
