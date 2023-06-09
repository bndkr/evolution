#include "ShaderEditor.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <string>
#include <iostream> // debug

void showShaderEditor(bool* showWindow, evolution::Program& program)
{
  static auto currentShader = evolution::defaultFragmentShaderSrc;

  if (*showWindow)
  {
    ImGui::Begin("Shader Editor", showWindow);

    ImGui::InputTextMultiline("", &currentShader, ImVec2(400, 200));

    static std::string currErrMsg;

    if (ImGui::Button("Compile"))
    {
      program.recompileFragShader(currentShader, &currErrMsg);
    }

    ImGui::Text(currErrMsg.c_str());

    ImGui::End();
  }
}