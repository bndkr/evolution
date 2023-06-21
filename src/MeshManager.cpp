#include "MeshManager.hpp"
#include "ProgramSelector.hpp"
#include "TextureManager.hpp"
#include "MeshImporter.hpp"

#include "Buffers.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <string>

void showMeshManagerWindow(
  std::map<std::string, std::unique_ptr<evolution::Mesh>>& meshes, bool& open)
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
    static std::string filePath;
    static std::string errMsg;
    ImGui::InputText("Name", &newName);
    ImGui::InputText("Filepath", &filePath);

    if (ImGui::Button("Create Mesh"))
    {
      errMsg = "";
      if (!newName.empty() && !meshes.count(newName))
      {
        try
        {
          meshes[newName] =
            std::make_unique<evolution::Mesh>(evolution::fromFile(filePath));
          errMsg = "";
          ImGui::CloseCurrentPopup();
        }
        catch (const std::exception& e)
        {
          errMsg = std::string("unable to create mesh: ") + e.what();
        }
      }
    }
    if (ImGui::Button("Cancel"))
      ImGui::CloseCurrentPopup();
    ImGui::Text(errMsg.c_str());
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
    auto availableShaders =
      evolution::getProgramSelector()->getAllValidProgramKeys();
    for (const auto& key : availableShaders)
    {
      if (ImGui::Selectable(key.c_str(), selectedShader == key))
      {
        selectedShader = key;
        meshes[selectedMesh]->useShader(selectedShader);
      }
    }

    ImGui::SeparatorText("Available Textures");

    evolution::Mesh* pTexture = meshes[selectedMesh].get();
    static std::string selectedTexture = "default";
    auto availableTextures =
      evolution::getTextureManager()->getAllTextures();
    for (const auto& key : availableTextures)
    {
      if (ImGui::Selectable(key.c_str(), selectedTexture == key))
      {
        selectedTexture = key;
        meshes[selectedMesh]->assignTexture(selectedTexture);
      }
    }
  }

  ImGui::End();
}