#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Buffers.hpp"
#include "Render.hpp"
#include "Setup.hpp"

#include <iostream>

int main(int argc, char** argv)
{
  auto window = evolution::setup();

  // Our state
  bool showDemoWindow = true;

  evolution::PositionBuffer vertices = {{-0.8f, -0.8f, 0.0f, 1.0f},
                                        {0.0f, 0.8f, 0.0f, 1.0f},
                                        {0.8f, -0.8f, 0.0f, 1.0f}};

  evolution::ColorBuffer colors = {{1.0f, 0.0f, 0.0f, 1.0f},
                                   {0.0f, 1.0f, 0.0f, 1.0f},
                                   {0.0f, 0.0f, 1.0f, 1.0f}};

  auto indexBuffer = evolution::IndexBuffer();
  auto mesh = evolution::Mesh(vertices, colors, indexBuffer);

  auto program = evolution::createProgram();

  // Main loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (showDemoWindow)
      ImGui::ShowDemoWindow(&showDemoWindow);

    ImGui::Render();
    // TODO: abstract away imgui stuff
    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);

    evolution::prepareRender(displayWidth, displayHeight);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    mesh.draw();

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
