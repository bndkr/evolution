#include "MeshManager.hpp"
#include "ProgramSelector.hpp"

#include "Buffers.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <string>

void showMeshManagerWindow(
  std::map<std::string, std::unique_ptr<evolution::Mesh>>& meshes,
  evolution::ProgramSelector& selector,
  bool& open)
{
  ImGui::Begin("Mesh Manager", &open, ImGuiWindowFlags_AlwaysAutoResize);

  if (ImGui::Button("Create new mesh"))
  {
    ImGui::OpenPopup("Create Mesh");
  }
  bool createMeshOpen = true;
  if (ImGui::BeginPopupModal(
        "Create Mesh", &createMeshOpen, ImGuiWindowFlags_AlwaysAutoResize))
  {
    static std::string newName;
    ImGui::InputText("Name", &newName);

    if (ImGui::Button("Create Mesh"))
    {
      if (!newName.empty() && !meshes.count(newName))
      {
        meshes[newName] = std::make_unique<evolution::Mesh>(
          evolution::createCubeMesh());
        ImGui::CloseCurrentPopup();
      }
    }
    if (ImGui::Button("Cancel"))
      ImGui::CloseCurrentPopup();
    ImGui::EndPopup();
  }

  ImGui::SeparatorText("Available Meshes");
  if (meshes.empty())
    return;

  static std::string selectedMesh = "";
  for (const auto& mesh : meshes)
  {
    if (ImGui::Selectable(mesh.first.c_str(), selectedMesh == mesh.first))
      selectedMesh = mesh.first;
  }

  if (meshes.count(selectedMesh))
  {
    ImGui::SeparatorText("Position");

    ImGui::SliderFloat3(
      "##position", &(meshes[selectedMesh]->getPostion()->x), -10.f, 10.f);

    ImGui::SeparatorText("Available Shaders");

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