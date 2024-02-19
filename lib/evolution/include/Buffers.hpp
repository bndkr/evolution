#ifndef EVOLUTION_BUFFERS_HPP
#define EVOLUTION_BUFFERS_HPP

#include <vector>

#include <string>

namespace evolution
{
  class Program;
  class Camera;
  class ProgramSelector;

  class Texture;

  struct Float4
  {
    Float4() : x(0.f), y(0.f), z(0.f), w(0.f) { }
    Float4(const float x, const float y, const float z, const float w)
      : x(x), y(y), z(z), w(w)
    {
    }
    float x;
    float y;
    float z;
    float w;
  };

  struct Float3
  {
    Float3() : x(0.f), y(0.f), z(0.f) { }

    Float3(const float x, const float y, const float z) : x(x), y(y), z(z) { }
    float x;
    float y;
    float z;
  };

  struct Float2
  {
    Float2() : x(0.f), y(0.f) { }
    Float2(const float x, const float y) : x(x), y(y) { }
    float x;
    float y;
  };

  struct Mat4;

  struct PositionInfo
  {
    Float3 position;
    Float3 rotation; // how does this work? do we need quaternions?
    // add scale?
  };

  typedef std::vector<Float3> PositionBuffer;
  typedef std::vector<Float4> ColorBuffer;
  typedef std::vector<Float2> TextureCoordBuffer;
  typedef std::vector<Float3> NormalVectorBuffer;
  typedef std::vector<uint32_t> IndexBuffer;

  struct MeshBuffers
  {
    PositionBuffer positions;
    ColorBuffer colors;
    TextureCoordBuffer texture;
    NormalVectorBuffer normals;
    IndexBuffer indices;
  };

  struct Vertex
  {
    Float3 position;
    Float4 color;
    Float2 textureCoords;
    Float3 normals;
  };

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

  class Mesh
  {
  public:
    Mesh(const MeshBuffers& buffers,
         const BufferDataUsage usage = BufferDataUsage::DynamicDraw);

    // Mesh();

    ~Mesh();

    // delete the copy, assignment operators
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    // move constructor
    Mesh(Mesh&& other);
    // assignment operator
    Mesh& operator=(Mesh&& other);

    void useShader(const std::string& shader);

    void setPosition(const Float3& newPos);
    void movePostion(const Float3& delta);

    void setRotation(const Float3& rotation);

    void rotate(const Float3& delta);

    void assignTexture(const std::string& texName);

    Float3* getPostion();
    Float3* getRotation();

    Mat4 getWorldSpaceTransformation();

    // draws the mesh using a viewpoint.
    void draw(const Camera& camera);

  protected:
    // Keep track of OpenGL buffer IDs
    uint32_t m_posBufferId = 0;
    uint32_t m_textureBufferId = 0;
    uint32_t m_indexBufferId = 0;
    uint32_t m_vaoId = 0;

    std::string m_currProgram = "";
    std::string m_currTexture = "";

    size_t m_numUniqueVertices = 0;
    size_t m_numVertices = 0;

    PositionInfo m_position;

    void release();
  };

  // TODO: add factory methods (createCube, createSphere, create...)
  Mesh createCubeMesh();

  Mesh createTextureQuad();

  MeshBuffers getQuadBuffers();

} // namespace evolution

#endif