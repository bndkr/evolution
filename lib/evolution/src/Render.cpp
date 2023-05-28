#include "Render.hpp"

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

  void prepareRender(int width, int height)
  {
    glViewport(0, 0, width, height);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
  }
} // namespace evolution
