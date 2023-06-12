#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "Buffers.hpp"
#include "ProgramSelector.hpp"
#include "Setup.hpp"
#include "Camera.hpp"

#include "ShaderEditor.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace
{
  void setupImgui(GLFWwindow* window)
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 430");
  }
} // namespace

int main(int argc, char** argv)
{
  uint32_t width = 1600;
  uint32_t height = 900;

  auto window = evolution::setup(/*enable3D=*/true, width, height);
  setupImgui(window);

  evolution::ProgramSelector programSelector;
  auto pDefaultProgram = programSelector.getProgram("default");
  if (!pDefaultProgram)
    throw std::runtime_error("unable to initialize default program");

  auto mesh =
    evolution::createCubeMesh(&programSelector);
  mesh.useShader("default");

  mesh.movePostion(evolution::Float3{0.0f, 0.0f, -2.0f});

  static float initialColor[4] = {0.0f, 1.0f, 1.0f, 1.0f};
  pDefaultProgram->addUniform(initialColor, 4, "un_color");

  evolution::Camera camera(width, height);

  // Main loop
  // let's start off leaving the main loop client-side. this allows
  // the client more flexibility over events and state.
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    mesh.rotate(evolution::Float3{0.01f, 0.008f, 0.009f});


    ImGui::Begin("yep, it's me again.", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
    static float color[4] = {0};
    if (ImGui::ColorPicker4("pick a color for the cube!", color))
    {
      pDefaultProgram->addUniform(color, 4, "un_color");
    }

    ImGui::End();

    ImGui::ShowDemoWindow();

    static bool shaderEditorOpen = true;
    showShaderEditor(&shaderEditorOpen, programSelector);

    // ImGui::ShowDemoWindow();

    ImGui::Render();

    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);

    glViewport(0, 0, displayWidth, displayHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mesh.draw(camera);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
