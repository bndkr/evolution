#include "Render.hpp"

#include "color_console/color.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

namespace
{
  uint32_t compileShader(uint32_t type, const std::string& src)
  {
    uint32_t id = glCreateShader(type);
    auto srcStr = src.c_str();
    glShaderSource(id, 1, &srcStr, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (!result)
    {
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
      std::vector<char> errorMsg(length);
      glGetShaderInfoLog(id, length, &length, errorMsg.data());
      std::string errorMsgStr(errorMsg.data(), errorMsg.size());
      // todo: let client code handle the error
      std::cout << "Error compiling shader: " << errorMsgStr << std::endl;
      glDeleteShader(id);
      return 0;
    }
    return id;
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
} // namespace

namespace evolution
{
  uint32_t createProgram(const std::string& vertexShader,
                         const std::string& fragmentShader)
  {
    auto program = glCreateProgram();

    auto vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShader);
    auto fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    glUseProgram(program);
    return program;
  }

  void setupOpenGL()
  {
    glDebugMessageCallback(glErrorCallback, nullptr);
    glEnable(GL_DEBUG_OUTPUT);

    // todo: add game engine logging module
    std::cout << "opengl version: " << glGetString(GL_VERSION) << std::endl;
  }

  void prepareRender(int width, int height)
  {
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
} // namespace evolution
