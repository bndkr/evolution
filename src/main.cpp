#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include "Buffers.hpp"
#include "Shader.hpp"
#include "Setup.hpp"
#include "Camera.hpp"
#include "Projection.hpp" // for debugging projection matrix

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

  // Our state
  evolution::PositionBuffer vertices = {{-0.8f, -0.8f, 0.0f, 1.0f},
                                        {0.0f, 0.8f, 0.0f, 1.0f},
                                        {0.8f, -0.8f, 0.0f, 1.0f}};

  evolution::ColorBuffer colors = {{1.0f, 0.0f, 0.0f, 1.0f},
                                   {0.0f, 1.0f, 0.0f, 1.0f},
                                   {0.0f, 0.0f, 1.0f, 1.0f}};

  auto indexBuffer = evolution::IndexBuffer();

  auto mesh =
    evolution::Mesh(vertices, colors, indexBuffer, evolution::PositionInfo());

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

    ImGui::Begin("hello");
    {
      if (ImGui::ColorPicker4("pick your triangle color!", initialColor))
      {
        program.addUniform(initialColor, 4, "un_color");
      }
      static float position1[4] = {0};

      ImGui::SliderFloat4("position1", position1, -5.f, 5.f);

      evolution::Mat4 m = evolution::identityMatrix();
      m.m[3] = position1[0];
      m.m[7] = position1[1];
      m.m[11] = position1[2];
      // m.m[15] = position1[3];
      program.addUniform(m.m, 16, "un_modelMatrix");

      static float cameraPosition[4] = {0};
      ImGui::SliderFloat4("camera position", cameraPosition, -5.f, 5.f);
      auto cam = evolution::identityMatrix();
      cam.m[3] = cameraPosition[0];
      cam.m[7] = cameraPosition[1];
      cam.m[11] = cameraPosition[2];
      // cam.m[15] = cameraPosition[3];
      // program.addUniform(cam.m, 16, "un_eyeMatrix");
    }
    ImGui::End();

    ImGui::Render();

    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);

    glViewport(0, 0, displayWidth, displayHeight);
    glClear(GL_COLOR_BUFFER_BIT);

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
