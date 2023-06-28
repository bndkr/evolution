#include "ShaderEditor.hpp"
#include "ProgramSelector.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <string>
#include <stdexcept>

namespace
{
  const std::string defaultVertShader = R"(
#version 440

layout(location=0) in vec4 positionIn;
layout(location=1) in vec4 colorIn;
layout(location=2) in vec2 texCoordsIn;

uniform mat4 un_modelMatrix;
uniform mat4 un_eyeMatrix;
uniform mat4 un_projMatrix;

out vec4 colorPass;
out vec2 texCoordsPass;

void main(void)
{
  gl_Position = (un_projMatrix * un_eyeMatrix * un_modelMatrix) * positionIn;
  colorPass = colorIn;
  texCoordsPass = texCoordsIn;
})";
  const std::string defaultFragShader = R"(
#version 440

in vec4 colorPass;
in vec2 texCoordsPass;
out vec4 colorOut;

uniform sampler2D un_texture;
void main(void)
{
  colorOut = texture(un_texture, texCoordsPass);
}
)";
} // namespace

void showShaderEditor(bool* showWindow)
{
  if (*showWindow)
  {
    ImGui::Begin(
      "Shader Editor", showWindow, ImGuiWindowFlags_AlwaysAutoResize);

    auto validShaders =
      evolution::getProgramSelector()->getAllValidProgramKeys();

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
          std::string error;
          evolution::getProgramSelector()->addProgram(
            defaultVertShader, defaultFragShader, newShaderName, &error);
          if (!error.empty())
            throw std::runtime_error("a default shader failed to compile: " +
                                     error);
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

    evolution::Program* currProgram =
      evolution::getProgramSelector()->getProgram(selectedShader);
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