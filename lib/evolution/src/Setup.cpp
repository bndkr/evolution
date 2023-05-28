#include "Setup.hpp"

#include "color_console/color.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace
{
  void glfwErrorCallback(int error, const char* description)
  {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
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
      ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

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
    if (!glfwInit())
      exit(1);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // debug mode for logging
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    // Create window with graphics context
    auto window = glfwCreateWindow(width, height, name, nullptr, nullptr);
    if (!window)
      exit(1);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (glewInit() != GLEW_OK)
    {
      std::cerr << "error initializing glew" << std::endl;
      exit(1);
    }
    return window;
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
  void setupOpenGL()
  {
    glDebugMessageCallback(glErrorCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);

    // todo: add game engine logging module
    std::cout << "opengl version: " << glGetString(GL_VERSION) << std::endl;
  }
} // namespace

namespace evolution
{
  GLFWwindow* setup()
  {
    auto* window = setupGlfwWindow(1280, 720, "Evolution Game Engine");
    setupImgui(window);
    setupOpenGL();
    return window;
  }
} // namespace evolution