#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Buffers.hpp"
#include "Render.hpp"
#include "color_console/color.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <vector>

namespace
{
  void glfwErrorCallback(int error, const char* description)
  {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
  }

  void GLAPIENTRY glErrorCallback(GLenum source,
                                  GLenum type,
                                  GLuint id,
                                  GLenum severity,
                                  GLsizei length,
                                  const GLchar* message,
                                  const void* userParam)
  {
    if (severity == GL_DEBUG_SEVERITY_HIGH)
      std::cout << dye::purple_on_white(std::string(message, length))
                << std::endl;
    if (severity == GL_DEBUG_SEVERITY_MEDIUM)
      std::cout << dye::red(std::string(message, length)) << std::endl;
    if (severity == GL_DEBUG_SEVERITY_LOW)
      std::cout << dye::yellow_on_white(std::string(message, length))
                << std::endl;
    // if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
    //   std::cout << dye::light_aqua(std::string(message, length)) <<
    //   std::endl;
  }

  void setupImgui(GLFWwindow* window)
  {
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
    ImGui_ImplOpenGL3_Init("#version 430");
  }

  GLFWwindow* setupGlfwWindow(const int width,
                              const int height,
                              const char* name)
  {
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // debug mode for logging
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Create window with graphics context
    GLFWwindow* window =
      glfwCreateWindow(width, height, name, nullptr, nullptr);
    if (!window) exit(1);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (glewInit() != GLEW_OK)
    {
      std::cerr << "error initializing glew" << std::endl;
      exit(1);
    }
    return window;
  }
} // namespace

int main(int argc, char** argv)
{
  auto window = setupGlfwWindow(1280, 720, "Evolution Game Engine");

  setupImgui(window);
  glDebugMessageCallback(glErrorCallback, nullptr);
  glEnable(GL_DEBUG_OUTPUT);

  std::cout << "opengl version: " << glGetString(GL_VERSION) << std::endl;

  // Our state
  bool showDemoWindow = true;

  evolution::PositionBuffer vertices = { { -0.8f, -0.8f, 0.0f, 1.0f },
                                         { 0.0f, 0.8f, 0.0f, 1.0f },
                                         { 0.8f, -0.8f, 0.0f, 1.0f } };

  evolution::ColorBuffer colors = { { 1.0f, 0.0f, 0.0f, 1.0f },
                                    { 0.0f, 1.0f, 0.0f, 1.0f },
                                    { 0.0f, 0.0f, 1.0f, 1.0f } };

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

    if (showDemoWindow) ImGui::ShowDemoWindow(&showDemoWindow);

    ImGui::Render();
    int displayWidth, displayHeight;
    glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
    glViewport(0, 0, displayWidth, displayHeight);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
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
