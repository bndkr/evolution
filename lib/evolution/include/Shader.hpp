#ifndef EVOLUTION_SHADER_HPP
#define EVOLUTION_SHADER_HPP

#include <string>
#include <vector>

namespace evolution
{
  const std::string defaultVertexShaderSrc = R"(
#version 440

layout(location=0) in vec4 positionIn;
layout(location=1) in vec4 colorIn;
layout(location=2) in vec2 texCoordsIn;

uniform mat4 un_modelMatrix;
uniform mat4 un_eyeMatrix;
uniform mat4 un_projMatrix;

out vec4 colorPass;
out vec2 texCoordsPass;

void main(void)
{
  gl_Position = (un_projMatrix * un_eyeMatrix * un_modelMatrix) * positionIn;
  // gl_Position = (un_eyeMatrix * un_modelMatrix) * positionIn;
  // gl_Position = positionIn;
  colorPass = colorIn;
  texCoordsPass = texCoordsIn;
}
)";

  const std::string defaultFragmentShaderSrc = R"(
#version 440

in vec4 colorPass;
in vec2 texCoordsPass;
out vec4 colorOut;

uniform vec4 un_color;

void main(void)
{
  colorOut = colorPass;
  // colorOut = un_color;
}
)";

  class Program
  {
  public:
    Program(const std::string& vertexShaderSrc = defaultVertexShaderSrc,
            const std::string& fragmentShaderSrc = defaultFragmentShaderSrc,
            std::string* errMsg = nullptr);

    ~Program();

    Program(const Program&) = delete;
    Program& operator=(const Program&) = delete;

    Program(Program&& other);
    Program& operator=(Program&& other);

    std::string& getVertexShaderSrc();
    std::string& getFragmentShaderSrc();

    void bind();
    void unbind();

    void recompileFragShader(const std::string& fragmentShaderSrc,
                             std::string* errMsg = nullptr);
    void recompileVertexShader(const std::string& vertexShaderSrc,
                               std::string* errMsg = nullptr);

    void recompileProgram(const std::string& fragmentShaderSrc,
                          const std::string& vertexShaderSrc,
                          std::string* errMsg);

    void recompileProgram(std::string* errMsg);

    void addUniform(const float* vals, size_t num, std::string name);
    void addUniform(const uint32_t* vals, size_t num, std::string name);
    void addUniform(const int32_t* vals, size_t num, std::string name);

  private:
    uint32_t m_programID = 0;
    std::string m_vertexSrc;
    std::string m_fragSrc;

    void release();
  };
} // namespace evolution

#endif