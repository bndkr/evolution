#include "Batch.hpp"

#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <stdexcept>

// temp
#include <iostream>

namespace evolution
{
  Batch::Batch(const MeshBuffers& buffers,
               const std::vector<BatchObject>& objects)
    : m_buffers(buffers), m_objects(objects)
  {
    auto indices = buffers.indices;
    auto colors = buffers.colors;
    auto textureCoods = buffers.texture;
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

    m_numUniqueVertices = buffers.positions.size() * objects.size();
    m_numVertices = indices.size() * objects.size();
    size_t vertexSize = 12 * sizeof(float);
    m_objectSize = buffers.positions.size() * vertexSize;
    std::vector<Vertex> vertices;
    IndexBuffer batchedIndices;

    for (size_t objectIdx = 0; objectIdx < objects.size(); objectIdx++)
    {
      for (size_t i = 0; i < indices.size(); i++)
      {
        batchedIndices.push_back(indices[i] +
                                 (objectIdx * buffers.positions.size()));
      }

      for (size_t i = 0; i < buffers.positions.size(); i++)
      {
        Float3 newPosition{
          buffers.positions[i].x + objects[objectIdx].position.x,
          buffers.positions[i].y + objects[objectIdx].position.y,
          buffers.positions[i].z + objects[objectIdx].position.z};
        // TODO: support rotation

        vertices.push_back(
          Vertex{newPosition, colors[i], textureCoods[i], buffers.normals[i]});
      }
    }

    m_data.resize(m_objectSize * objects.size());
    std::memcpy(m_data.data(), vertices.data(), m_objectSize * objects.size());

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
                 sizeof(uint32_t) * batchedIndices.size(),
                 batchedIndices.data(),
                 GL_DYNAMIC_DRAW);

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

  void Batch::moveObject(const std::string& key, const Float3& delta)
  {
    // get the index of the object
    int32_t objectIdx = -1;
    uint32_t i = 0;
    for (const auto& item : m_objects)
    {
      if (item.name == key)
        objectIdx = i;
      i++;
    }

    std::cout << "object:" << objectIdx << std::endl;

    if (objectIdx == -1)
      throw std::runtime_error("batched object with key (" + key +
                               ") does not exist.");

    size_t objectOffset = m_objectSize * objectIdx;
    for (size_t i = 0; i < m_numUniqueVertices; i++)
    {
      m_data[objectOffset + (i * sizeof(Vertex))] += delta.x;
      m_data[objectOffset + (i * sizeof(Vertex)) + 1] += delta.x;
      m_data[objectOffset + (i * sizeof(Vertex)) + 2] += delta.x;
    }

    // create and bind the vertex array object
    glBindVertexArray(m_vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, m_posBufferId);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vertex) * m_numUniqueVertices,
                 m_data.data(),
                 GL_DYNAMIC_DRAW);
  }
} // namespace evolution
