#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include <vector>
#include <iostream>

#include "Render.hpp"

namespace
{
  void glfwErrorCallback(int error, const char* description)
  {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
  }

  void glErrorCallback(GLenum source,
                       GLenum type,
                       GLuint id,
                       GLenum severity,
                       GLsizei length,
                       const GLchar* pMessage,
                       const void* pUserParam)
  {
    std::string msg(pMessage, length);
    std::cout << "error: " << msg << std::endl;
  }
}


int main(int, char**)
{
  glfwSetErrorCallback(glfwErrorCallback);
  if (!glfwInit()) return 1;

  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // Create window with graphics context
  GLFWwindow* window = glfwCreateWindow(
    1280, 720, "Evolution Game Engine", nullptr, nullptr);
  if (!window) return 1;

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  if (glewInit() != GLEW_OK)
  {
    std::cerr << "error initializing glew" << std::endl;
    return 1;
  }
  std::cout << "opengl version: " << glGetString(GL_VERSION) << std::endl;

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |=
    ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
    ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  glDebugMessageCallback(glErrorCallback, nullptr);

  // Our state
  bool showDemoWindow = true;
  ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  std::vector<float> triangle{ -1.f, -.5f, 0.f, .5f, .5f, -.5f };

  auto buffer = evolution::generateVertexBuffer(
    triangle.data(), triangle.size() * sizeof(float), evolution::StaticDraw);

  // specify shader
  auto shader = evolution::createShader(evolution::defaultVertexShaderSrc,
                                        evolution::defaultFragmentShaderSrc);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);

  // Main loop
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);

    ImGui::Render();
    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
    glViewport(0, 0, displayWidth, displayHeight);
    glClearColor(clearColor.x * clearColor.w,
                 clearColor.y * clearColor.w,
                 clearColor.z * clearColor.w,
                 clearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glDrawArrays(GL_TRIANGLES, 0, 3);

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
