#include "Shader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <stdexcept>

namespace
{
  uint32_t compileShader(uint32_t type,
                         const std::string& src,
                         std::string* errMsg)
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
      *errMsg = errorMsgStr;
      return 0;
    }
    return id;
  }

  uint32_t createProgram(const std::string& vertexStc,
                         const std::string fragSrc,
                         std::string* errMsg)
  {
    uint32_t programId = glCreateProgram();
    auto vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexStc, errMsg);
    auto fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragSrc, errMsg);

    if (errMsg && !errMsg->empty())
      return 0;

    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);
    glValidateProgram(programId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return programId;
  }
} // namespace

namespace evolution
{
  Program::Program(const std::string& vertexShaderSrc,
                   const std::string& fragmentShaderSrc,
                   std::string* errMsg)
    : m_vertexSrc(vertexShaderSrc), m_fragSrc(fragmentShaderSrc)
  {

    m_programID = createProgram(vertexShaderSrc, fragmentShaderSrc, errMsg);
    bind();
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

  void Program::recompileFragShader(const std::string& fragmentShaderSrc,
                                    std::string* errMsg)
  {
    glDeleteProgram(m_programID);
    m_programID = createProgram(m_vertexSrc, fragmentShaderSrc, errMsg);

    bind();
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
      glUniformMatrix4fv(location, 1, /*transpose=*/GL_TRUE, vals);
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
