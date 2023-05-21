#ifndef RENDER_HPP
#define RENDER_HPP

#include <string>

namespace evolution
{
  const std::string defaultVertexShaderSrc = R"(
#version 400

layout(location=0) in vec4 positionIn;
layout(location=1) in vec4 colorIn;

out vec4 colorOut;

void main()
{
  gl_Position = positionIn;
  colorOut = colorIn;
}
)";

  const std::string defaultFragmentShaderSrc = R"(
#version 400

in vec4 colorIn;
out vec4 colorOut;

void main()
{
  colorOut = colorIn;
}
)";

  uint32_t createShader(const std::string& vertexShader,
                        const std::string& fragmentShader);

} // namespace evolution
#endif