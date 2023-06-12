#include "Setup.hpp"

#include "color_console/color.hpp"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace
{
  void glfwErrorCallback(int error, const char* description)
  {
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
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
      std::cout << dye::red(std::string(message, length)) << std::endl;
    if (severity == GL_DEBUG_SEVERITY_MEDIUM)
      std::cout << dye::red(std::string(message, length)) << std::endl;
    if (severity == GL_DEBUG_SEVERITY_LOW)
      std::cout << dye::yellow(std::string(message, length)) << std::endl;
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
    glClearColor(
      0.5f,
      0.5f,
      0.5f,
      1.0f); // background color. Does this need to be in the main loop?
  }

  void enable3D()
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); // not sure why GL_LESS doesn't work
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);    // why back and not front?
    glFrontFace(GL_CCW);
  }
} // namespace

namespace evolution
{
  GLFWwindow* setup(const bool enable3DMode, unsigned int width, unsigned int height)
  {
    auto* window = setupGlfwWindow(width, height, "Evolution Game Engine");
    setupOpenGL();
    if (enable3DMode)
      enable3D();
    return window;
  }
} // namespace evolution