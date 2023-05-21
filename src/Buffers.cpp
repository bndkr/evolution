#define GLEW_STATIC
#include "Buffers.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace evolution
{
  Mesh::Mesh(const VertexBuffer& vb,
             IndexBuffer& ib,
             const BufferDataUsage usage = BufferDataUsage::StaticDraw)
  {
    if (ib.size() == 0) // no index buffer
    {
      // generate a default one
      for (uint32_t i = 0; i < vb.size(); i++)
      {
        ib.push_back(i);
      }
    }

    if (vb.size() != ib.size())
    {
      throw std::runtime_error(
        "invalid mesh setup, buffer count not consistent");
    }
    uint32_t bufferSize = vb.size();

    // create a vertex buffer
    uint32_t buffId = 0;
    glGenBuffers(1, &buffId);
    if (!buffId) throw std::runtime_error("buffer generation failed");
    glBindBuffer(GL_ARRAY_BUFFER, buffId);

    glBufferData(
      GL_ARRAY_BUFFER, vb.size() * sizeof(VertexType), vb.data(), usage);
  }
} // namespace evolution