#ifndef EVOLUTION_BUFFERS_HPP
#define EVOLUTION_BUFFERS_HPP

#include <vector>

namespace evolution
{
  class Program;
  class Camera;

  struct Float4
  {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float w = 0.0f;
  };

  struct Float3
  {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
  };

  struct Mat4;

  struct PositionInfo
  {
    Float3 position;
    Float3 rotation; // how does this work? do we need quaternions?
    // add scale?
  };

  typedef std::vector<Float4> PositionBuffer;
  typedef std::vector<Float4> ColorBuffer;
  // ... add more as needed (etc. normal, texture coords)
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
         const PositionInfo posInfo,
         const BufferDataUsage usage = BufferDataUsage::DynamicDraw);

    void setPosition(Float3 newPos);
    void movePostion(Float3 delta);

    // TODO: I don't think 3 floats can uniquely identify all possible rotations
    void setRotation(Float3 rotation);

    void rotate(Float3 delta);

    Float3 getPostion();
    Float3 getRotation();

    Mat4 getWorldSpaceTransformation();

    ~Mesh();

    // draws the mesh using a program and a viewpoint. Assumes the program is
    // already bound.
    void draw(Program& program, const Camera& camera);

  private:
    // Keep track of OpenGL buffer IDs
    uint32_t m_posBufferId;
    uint32_t m_colBufferId;
    uint32_t m_indexBufferId;
    uint32_t m_vaoId;

    size_t m_numUniqueVertices;
    size_t m_numVertices;

    PositionInfo m_position;
  };
} // namespace evolution

#endif