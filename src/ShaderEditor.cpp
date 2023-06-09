#include "ShaderEditor.hpp"

#include <imgui/imgui.h>

static bool shaderEditorOpen(true);

void showShaderEditor()
{
  if (shaderEditorOpen)
  {
    ImGui::Begin("Shader Editor", &shaderEditorOpen);
    // create a multi-line text box that is dynamic in size
    // (copied from imgui_demo.cpp)
    struct Funcs
    {
      static int MyResizeCallback(ImGuiInputTextCallbackData* data)
      {
        if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
        {
          ImVector<char>* str = (ImVector<char>*)data->UserData;
          IM_ASSERT(str->begin() == data->Buf);
          str->resize(data->BufSize);
          data->Buf = str->begin();
        }
        return 0;
      }
      static bool MyInputTextMultiline(const char* label,
                                       ImVector<char>* str,
                                       const ImVec2& size = ImVec2(0, 0),
                                       ImGuiInputTextFlags flags = 0)
      {
        IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
        return ImGui::InputTextMultiline(
          label,
          str->begin(),
          (size_t)str->size(),
          size,
          flags | ImGuiInputTextFlags_CallbackResize,
          Funcs::MyResizeCallback,
          (void*)str);
      }
    };

    static ImVector<char> str;
    if (str.empty())
      str.push_back(0);
    Funcs::MyInputTextMultiline(
      "##MyStr", &str, ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16));
    ImGui::End();
  }
}