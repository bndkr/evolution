#include "MeshImporter.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stdexcept>

namespace evolution
{
  void fromFile(const std::string& filename)
  {
    Assimp::Importer importer;

    auto pScene = importer.ReadFile(
      filename,
      aiProcess_CalcTangentSpace | aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if (!pScene)
      throw std::runtime_error("i failed you.");

    if (!pScene->mMeshes)
      throw std::runtime_error("scene has no meshes");
    


  }
} // namespace evolution
