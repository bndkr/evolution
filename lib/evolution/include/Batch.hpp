#ifndef EVOLUTION_BATCH
#define EVOLUTION_BATCH

#include "Buffers.hpp"

#include <set>

namespace evolution
{
  struct BatchObject
  {
    std::string name;
    Float3 position;
    Float3 rotation;
    // color, texture...
  };


  class Batch : public Mesh
  {
  public:
    Batch(const MeshBuffers& buffers, const std::vector<BatchObject>& objects);

    std::set<std::string> getAllObjectNames();

    void moveObject(const std::string& key, const Float3& delta);
    void setObjectPos(const std::string& key, const Float3& newPos);

    void rotateObject(const std::string& key, const Float3& delta);
    void setObjectRotation(const std::string& key, const Float3& newRotation);

  private:
    MeshBuffers m_buffers;
    size_t m_objectSize;
    std::vector<BatchObject> m_objects;
    std::vector<float> m_data;
  };
} // namespace evolution

#endif