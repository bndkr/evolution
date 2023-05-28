#ifndef EVOLUTION_BUFFERS_HPP
#define EVOLUTION_BUFFERS_HPP

#include <vector>

namespace evolution
{
  struct Float4
  {
    float x;
    float y;
    float z;
    float w;
  };

  typedef std::vector<Float4> PositionBuffer;
  typedef std::vector<Float4> ColorBuffer;
  // ... add more as needed (etc. normal)
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
    Mesh(const PositionBuffer& positions,
         const ColorBuffer& colors,
         IndexBuffer& indices,
         const BufferDataUsage usage = BufferDataUsage::StaticRead);

    ~Mesh();

    void draw();

  private:
    uint32_t m_posBufferId;
    uint32_t m_colBufferId;
    uint32_t m_indexBufferId;
    uint32_t m_vaoId;

    size_t m_numVertices;
  };
} // namespace evolution

#endif