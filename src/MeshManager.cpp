#include "MeshManager.hpp"
#include "ProgramSelector.hpp"

#include "Buffers.hpp"

#include <imgui/imgui.h>

#include <string>

void showMeshManagerWindow(
  std::map<std::string, std::unique_ptr<evolution::Mesh>>& meshes,
  const evolution::ProgramSelector& selector,
  bool& open)
{
  ImGui::Begin("Mesh Manager", &open, ImGuiWindowFlags_AlwaysAutoResize);

  if (meshes.empty())
    return;

  static std::string selectedMesh = "";
  for (const auto& mesh : meshes)
  {
    if (ImGui::Selectable(mesh.first.c_str(), selectedMesh == mesh.first))
      selectedMesh = mesh.first;
  }

  ImGui::SeparatorText("Available Shaders");
  
  if (meshes.count(selectedMesh))
  {
    evolution::Mesh* pMesh = meshes[selectedMesh].get();
    static std::string selectedShader = "default";
    auto availableShaders = selector.getAllValidProgramKeys();
    for (const auto& key : availableShaders)
    {
      if (ImGui::Selectable(key.c_str(), selectedShader == key))
      {
        selectedShader = key;
        meshes[selectedMesh]->useShader(selectedShader);
      }
    }
  }

  ImGui::End();
}