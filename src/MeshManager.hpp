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
  std::map<std::string, std::unique_ptr<evolution::Mesh>>& meshes,
  const evolution::ProgramSelector& selector,
  bool& open);

#endif