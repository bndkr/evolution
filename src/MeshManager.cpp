#include "MeshManager.hpp"

#include "Buffers.hpp"

#include <imgui/imgui.h>

#include <string>

void showMeshManagerWindow(
  std::map<std::string, std::unique_ptr<evolution::Mesh>>& meshes, bool& open)
{
  ImGui::Begin("Mesh Manager", &open, ImGuiWindowFlags_AlwaysAutoResize);

  static std::string selectedMesh = "default";
  for (auto&& mesh : meshes)
  {
    if (ImGui::Selectable(mesh.first.c_str(), selectedMesh == mesh.first))
      selectedMesh = mesh.first;
  }

  if (meshes.count(selectedMesh))
  {
    evolution::Mesh* pMesh = meshes[selectedMesh].get();
    ImGui::Text("Mesh name: %s", selectedMesh);

  }

  ImGui::End();
}