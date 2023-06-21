#include "Shader.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <stdexcept>
#include <iostream> // debugging

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
      if (errMsg)
        *errMsg = errorMsgStr;
      return 0;
    }
    return id;
  }

  uint32_t createProgram(const std::string& vertexStc,
                         const std::string fragSrc,
                         std::string* errMsg)
  {
    if (errMsg)
      errMsg->clear();
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
  }

  Program::~Program()
  {
    release();
  }

  Program::Program(Program&& other)
  {
    other.m_programID = 0;
    other.m_fragSrc.clear();
    other.m_vertexSrc.clear();
  }

  Program& Program::operator=(Program&& other)
  {
    if (this != &other)
    {
      release();
      std::swap(m_programID, other.m_programID);
      std::swap(m_fragSrc, other.m_fragSrc);
      std::swap(m_vertexSrc, other.m_vertexSrc);
    }
    return other;
  }

  std::string& Program::getVertexShaderSrc()
  {
    return m_vertexSrc;
  }

  std::string& Program::getFragmentShaderSrc()
  {
    return m_fragSrc;
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
    m_fragSrc = fragmentShaderSrc;
    m_programID = createProgram(m_vertexSrc, fragmentShaderSrc, errMsg);
  }

  void Program::recompileVertexShader(const std::string& vertexShaderSrc,
                                      std::string* errMsg)
  {
    glDeleteProgram(m_programID);
    m_vertexSrc = vertexShaderSrc;
    m_programID = createProgram(vertexShaderSrc, m_fragSrc, errMsg);
  }

  void Program::recompileProgram(const std::string& fragmentShaderSrc,
                                 const std::string& vertexShaderSrc,
                                 std::string* errMsg)
  {
    glDeleteProgram(m_programID);
    m_vertexSrc = vertexShaderSrc;
    m_fragSrc = fragmentShaderSrc;
    m_programID = createProgram(vertexShaderSrc, fragmentShaderSrc, errMsg);
  }

  void Program::recompileProgram(std::string* errMsg)
  {
    recompileProgram(m_fragSrc, m_vertexSrc, errMsg);
  }

  void Program::addUniform(const float* vals, size_t num, std::string name)
  {
    bind();
    auto location = glGetUniformLocation(m_programID, name.c_str());
    if (num == 1)
      glUniform1f(location, vals[0]);
    else if (num == 2)
      glUniform2f(location, vals[0], vals[1]);
    else if (num == 3)
      glUniform3f(location, vals[0], vals[1], vals[2]);
    else if (num == 4)
      glUniform4f(location, vals[0], vals[1], vals[2], vals[3]);
    else if (num = 16)
      glUniformMatrix4fv(location, 1, /*transpose=*/GL_TRUE, vals);
    else
      throw std::runtime_error("invalid number of elements in array");
    unbind();
  }
  void Program::addUniform(const uint32_t* vals, size_t num, std::string name)
  {
    bind();
    auto location = glGetUniformLocation(m_programID, name.c_str());
    if (num == 1)
      glUniform1ui(location, vals[0]);
    else if (num == 2)
      glUniform2ui(location, vals[0], vals[1]);
    else if (num == 3)
      glUniform3ui(location, vals[0], vals[1], vals[2]);
    else if (num == 4)
      glUniform4ui(location, vals[1], vals[2], vals[3], vals[4]);
    else
      throw std::runtime_error("invalid number of elements in array");
    unbind();
  }
  void Program::addUniform(const int32_t* vals, size_t num, std::string name)
  {
    bind();
    auto location = glGetUniformLocation(m_programID, name.c_str());
    if (num == 1)
      glUniform1i(location, vals[0]);
    else if (num == 2)
      glUniform2i(location, vals[0], vals[1]);
    else if (num == 3)
      glUniform3i(location, vals[0], vals[1], vals[2]);
    else if (num == 4)
      glUniform4i(location, vals[1], vals[2], vals[3], vals[4]);
    else
      throw std::runtime_error("invalid number of elements in array");
    unbind();
  }

  void Program::release()
  {
    glDeleteProgram(m_programID);
    m_programID = 0;
  }
} // namespace evolution
