#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "Buffers.hpp"
#include "Shader.hpp"
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
  auto window = evolution::setup(/*enable3D=*/true);
  setupImgui(window);

  evolution::PositionBuffer vertices = {
    {-.5f, -.5f, .5f, 1.f},
    {-.5f, .5f, .5f, 1.f},
    {.5f, .5f, .5f, 1.f},
    {.5f, -.5f, .5f, 1.f},
    {-.5f, -.5f, -.5f, 1.f},
    {-.5f, .5f, -.5f, 1.f},
    {.5f, .5f, -.5f, 1.f},
    {.5f, -.5f, -.5f, 1.f},
  };

  evolution::ColorBuffer colors = {
    {0.f, 0.f, 1.f, 1.f},
    {1.f, 0.f, 0.f, 1.f},
    {0.f, 1.f, 0.f, 1.f},
    {1.f, 1.f, 0.f, 1.f},
    {1.f, 1.f, 1.f, 1.f},
    {1.f, 0.f, 0.f, 1.f},
    {1.f, 0.f, 1.f, 1.f},
    {0.f, 0.f, 1.f, 1.f},
  };
  evolution::IndexBuffer indexBuffer = {0, 2, 1, 0, 3, 2, 4, 3, 0, 4, 7, 3,
                                        4, 1, 5, 4, 0, 1, 3, 6, 2, 3, 7, 6,
                                        1, 6, 5, 1, 2, 6, 7, 5, 6, 7, 4, 5};

  auto mesh =
    evolution::Mesh(vertices, colors, indexBuffer, evolution::PositionInfo());

  mesh.movePostion(evolution::Float3{0.0f, 0.0f, -2.0f});
  auto program = evolution::Program();
  program.bind();

  static float initialColor[4] = {0.0f, 1.0f, 1.0f, 1.0f};
  program.addUniform(initialColor, 4, "un_color");

  evolution::Camera camera({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f});

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
      program.addUniform(color, 4, "un_color");
    }

    ImGui::End();

    ImGui::ShowDemoWindow();

    static bool shaderEditorOpen = true;
    showShaderEditor(&shaderEditorOpen, program);

    ImGui::Render();

    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);

    glViewport(0, 0, displayWidth, displayHeight);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mesh.draw(program, camera);

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
