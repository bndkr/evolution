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
      aiProcess_GenNormals | aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
    if (!pScene)
      throw std::runtime_error("cannot open file: " + filename);

    if (!pScene->mMeshes)
      throw std::runtime_error("scene has no meshes");

    auto mesh = pScene->mMeshes[0];
    auto numVertices = mesh->mNumVertices;
    auto numFaces = mesh->mNumFaces;
    PositionBuffer posBuffer;
    ColorBuffer colors;
    IndexBuffer indexBuffer;
    TextureCoordBuffer texCoords;
    NormalVectorBuffer normals;

    for (size_t i = 0; i < numVertices; i++)
    {
      auto vertex = mesh->mVertices[i];
      auto normal = mesh->mNormals[i];
      posBuffer.push_back(Float4{vertex.x, vertex.y, vertex.z, 1.0f});
      colors.push_back(Float4{vertex.z, vertex.x, vertex.y, 1.0f});
      normals.push_back(Float4{normal.x, normal.y, normal.z, 1.f});

      if (mesh->HasTextureCoords((uint32_t)0))
      {
        auto texCoord = mesh->mTextureCoords[0][i];
        texCoords.push_back(Float2{texCoord.x, texCoord.y});
      }
    }
    for (size_t i = 0; i < numFaces; i++)
    {
      auto face = mesh->mFaces[i];
      for (size_t j = 0; j < face.mNumIndices; j++)
      {
        indexBuffer.push_back(face.mIndices[j]);
      }
    }
    MeshBuffers buffers{posBuffer, colors, texCoords, normals, indexBuffer};
    return Mesh(buffers, DynamicDraw);
  }

  Mesh fromFile(const boost::filesystem::path& filename)
  {
    return fromFile(filename.string());
  }
} // namespace evolution
