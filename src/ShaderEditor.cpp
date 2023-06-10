#include "ShaderEditor.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <string>
#include <iostream> // debug

void showShaderEditor(bool* showWindow, evolution::Program& program)
{
  static auto currentFragShader = evolution::defaultFragmentShaderSrc;
  static auto currentVertexShader = evolution::defaultVertexShaderSrc;
  if (*showWindow)
  {
    ImGui::Begin("Shader Editor", showWindow, ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::BeginTabBar("My tab bar");
    // TODO: see how this works (it doesn't)
    if (ImGui::BeginTabItem("Vertex Shader"))
    {

    }
    if (ImGui::BeginTabItem("Fragment Shader"))
    {

    }

    ImGui::EndTabBar();

    ImGui::InputTextMultiline("Fragment Shader Source", &currentFragShader, ImVec2(400, 200));

    static std::string currErrMsg;

    if (ImGui::Button("Compile"))
    {
      program.recompileFragShader(currentFragShader, &currErrMsg);
    }

    ImGui::Text(currErrMsg.c_str());

    ImGui::End();
  }
}