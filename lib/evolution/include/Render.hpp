#ifndef EVOLUTION_RENDER_HPP
#define EVOLUTION_RENDER_HPP

#include <string>

namespace evolution
{
  const std::string defaultVertexShaderSrc = R"(
#version 400

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
#version 400

in vec4 colorPass;
out vec4 colorOut;

void main(void)
{
  colorOut = colorPass;
}
)";

  uint32_t createProgram(
    const std::string& vertexShader = defaultVertexShaderSrc,
    const std::string& fragmentShader = defaultFragmentShaderSrc);

  void setupOpenGL();

} // namespace evolution
#endif