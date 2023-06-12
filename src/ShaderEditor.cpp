#include "ShaderEditor.hpp"
#include "ProgramSelector.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <string>

void showShaderEditor(bool* showWindow, evolution::ProgramSelector& selector)
{
  if (*showWindow)
  {
    ImGui::Begin(
      "Shader Editor", showWindow, ImGuiWindowFlags_AlwaysAutoResize);

    auto validShaders = selector.getAllValidProgramKeys();

    if (ImGui::Button("Create New Shader"))
      ImGui::OpenPopup("Create Shader");

    bool createShaderOpen = true;
    if (ImGui::BeginPopupModal("Create Shader",
                               &createShaderOpen,
                               ImGuiWindowFlags_AlwaysAutoResize))
    {
      static std::string newShaderName;
      ImGui::InputText("Name", &newShaderName);

      if (ImGui::Button("Create Shader"))
      {
        if (!newShaderName.empty())
        {
          selector.addProgram(newShaderName);
          ImGui::CloseCurrentPopup();
        }
      }
      if (ImGui::Button("Cancel"))
        ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
    ImGui::Text("Shader List:");
    static std::string selectedShader = "default";
    for (const auto& key : validShaders)
    {
      if (ImGui::Selectable(key.c_str(), selectedShader == key))
        selectedShader = key;
    }
    auto text = "Currently editing shader: " + selectedShader;
    ImGui::SeparatorText(text.c_str());

    static std::string error = "";

    evolution::Program* currProgram = selector.getProgram(selectedShader);
    ImGui::Text("Vertex Shader");
    ImGui::InputTextMultiline("##Vertex Shader",
                              &(currProgram->getVertexShaderSrc()),
                              ImVec2(500, 300));
    ImGui::Text("Fragment Shader");
    ImGui::InputTextMultiline("##Fragment Shader",
                              &(currProgram->getFragmentShaderSrc()),
                              ImVec2(500, 300));
    if (ImGui::Button("Compile"))
    {
      currProgram->recompileProgram(&error);
      if (!error.empty())
      {
        ImGui::OpenPopup("Error");
      }
    }

    // TODO: add a uniform creation menu

    bool open = true;
    if (ImGui::BeginPopupModal(
          "Error", &open, ImGuiWindowFlags_AlwaysAutoResize))
    {
      ImGui::Text(error.c_str());
      if (ImGui::Button("Close"))
        ImGui::CloseCurrentPopup();
      ImGui::EndPopup();
    }
    ImGui::End();
  }
}