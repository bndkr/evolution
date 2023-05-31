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

out vec4 colorPass;

void main(void)
{
  gl_Position = positionIn;
  colorPass = colorIn;
}
)";

  const std::string defaultFragmentShaderSrc = R"(
#version 440

in vec4 colorPass;
out vec4 colorOut;

uniform vec4 un_color;

void main(void)
{
  // colorOut = colorPass;
  colorOut = un_color;
}
)";

  class Program
  {
  public:
    Program(const std::string& vertexShaderSrc = defaultVertexShaderSrc,
            const std::string& fragmentShaderSrc = defaultFragmentShaderSrc);

    ~Program();

    void bind();
    void unbind();

    void addUniform(const std::vector<float>& vals, std::string name);
    void addUniform(const std::vector<uint32_t>& vals, std::string name);
    void addUniform(const std::vector<int32_t>& vals, std::string name);

  private:
    uint32_t m_programID = 0;
  };
} // namespace evolution

#endif