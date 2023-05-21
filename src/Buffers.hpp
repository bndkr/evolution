#ifndef BUFFERS_HPP
#define BUFFERS_HPP

#include <vector>

namespace evolution
{
  typedef float VertexType;
  typedef std::vector<VertexType> VertexBuffer;
  typedef std::vector<uint32_t> IndexBuffer;

  // hint to OpenGL about how buffer data will be accessed
  enum BufferDataUsage
  {
    // Static usage (modified once, used many times)
    StaticDraw,
    StaticRead,

    // Dynamic usage (modified many times, used many times)
    DynamicDraw,
    DynamicRead,
    DynamicCopy,
  };

  // for now: force location types to be floats. is there rationale in
  // supporting other types?
  class Mesh
  {
  public:
    Mesh(const VertexBuffer& vb, IndexBuffer& ib, const BufferDataUsage usage);
  };
} // namespace evolution

#endif