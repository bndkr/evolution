#include "MeshImporter.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stdexcept>

namespace evolution
{
  Mesh fromFile(const std::string& filename)
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

    auto mesh = pScene->mMeshes[0];
    auto numVertices = mesh->mNumVertices;
    auto numFaces = mesh->mNumFaces;
    PositionBuffer posBuffer;
    ColorBuffer colors;
    IndexBuffer indexBuffer;
    for (size_t i = 0; i < numVertices; i++)
    {
      auto vertex = mesh->mVertices[i];
      posBuffer.push_back(Float4{vertex.x, vertex.y, vertex.z, 1.0f});
      colors.push_back(Float4{1.0f, vertex.x, 1.0f, 1.0f});
    }
    for (size_t i = 0; i < numFaces; i++)
    {
      auto face = mesh->mFaces[i];
      for (size_t j = 0; j < face.mNumIndices; j++)
      {
        indexBuffer.push_back(face.mIndices[j]);
      }
    }
    return Mesh(posBuffer, colors, indexBuffer, PositionInfo{}, DynamicDraw);
  }
} // namespace evolution
