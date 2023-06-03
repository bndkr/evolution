#include "Shader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <stdexcept>

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
      glDeleteShader(id);
      throw std::runtime_error(errorMsgStr);
    }
    return id;
  }
} // namespace

namespace evolution
{
  Program::Program(const std::string& vertexShaderSrc,
                   const std::string& fragmentShaderSrc)
  {
    m_programID = glCreateProgram();
    auto vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    auto fragmentShaderId =
      compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

    glAttachShader(m_programID, vertexShaderId);
    glAttachShader(m_programID, fragmentShaderId);
    glLinkProgram(m_programID);
    glValidateProgram(m_programID);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);
  }

  Program::~Program()
  {
    glDeleteProgram(m_programID);
  }

  void Program::bind()
  {
    glUseProgram(m_programID);
  }

  void Program::unbind()
  {
    glUseProgram(0);
  }

  void Program::addUniform(const float* vals, size_t num, std::string name)
  {
    auto location = glGetUniformLocation(m_programID, name.c_str());
    if (num == 1)
    {
      glUniform1f(location, vals[0]);
    }
    else if (num == 2)
    {
      glUniform2f(location, vals[0], vals[1]);
    }
    else if (num == 3)
    {
      glUniform3f(location, vals[0], vals[1], vals[2]);
    }
    else if (num == 4)
    {
      glUniform4f(location, vals[0], vals[1], vals[2], vals[3]);
    }
    else if (num = 16)
    {
      glUniformMatrix4fv(location, ) // TODO: 4x4 float matrix support
    }
    else
    {
      throw std::runtime_error("invalid number of elements in array");
    }
  }
  void Program::addUniform(const uint32_t* vals, size_t num, std::string name)
  {
    auto location = glGetUniformLocation(m_programID, name.c_str());
    if (num == 1)
    {
      glUniform1ui(location, vals[0]);
    }
    else if (num == 2)
    {
      glUniform2ui(location, vals[0], vals[1]);
    }
    else if (num == 3)
    {
      glUniform3ui(location, vals[0], vals[1], vals[2]);
    }
    else if (num == 4)
    {
      glUniform4ui(location, vals[1], vals[2], vals[3], vals[4]);
    }
    else
    {
      throw std::runtime_error("invalid number of elements in array");
    }
  }
  void Program::addUniform(const int32_t* vals, size_t num, std::string name)
  {
    auto location = glGetUniformLocation(m_programID, name.c_str());
    if (num == 1)
    {
      glUniform1i(location, vals[0]);
    }
    else if (num == 2)
    {
      glUniform2i(location, vals[0], vals[1]);
    }
    else if (num == 3)
    {
      glUniform3i(location, vals[0], vals[1], vals[2]);
    }
    else if (num == 4)
    {
      glUniform4i(location, vals[1], vals[2], vals[3], vals[4]);
    }
    else
    {
      throw std::runtime_error("invalid number of elements in array");
    }
  }
} // namespace evolution
