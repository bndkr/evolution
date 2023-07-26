#ifndef MESH_MANAGER_HPP
#define MESH_MANAGER_HPP

#include <memory>
#include <map>
#include <string>

namespace evolution
{
  class Mesh;
  class ProgramSelector;
} // namespace evolution

void showMeshManagerWindow(
  std::map<std::string, std::shared_ptr<evolution::Mesh>>& meshes,
  const std::string shaderPath,
  bool& open);

#endif