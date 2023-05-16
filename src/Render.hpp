#ifndef RENDER_HPP
#define RENDER_HPP

#define GLEW_STATIC
#include <GLFW/glfw3.h>

#include <string>

namespace evolution
{
  const std::string defaultVertexShaderSrc = R"(
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
  gl_Position = position;
}
)";

  const std::string defaultFragmentShaderSrc = R"(
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
  color = vec4(1.0, 0.0, 0.0, 1.0);
}
)";

  // hint to OpenGL about how buffer data will be accessed
  enum BufferDataUsage
  {
    // Static usage (modified once, used many times)
    StaticDraw = GL_STATIC_DRAW,
    StaticRead = GL_STATIC_READ,

    // Dynamic usage (modified many times, used many times)
    DynamicDraw = GL_DYNAMIC_DRAW,
    DynamicRead = GL_DYNAMIC_READ,
    DynamicCopy = GL_DYNAMIC_COPY
  };

  typedef GLuint BufferIdx;

  /* Wrapper to OpenGL3 functionality. Remains a state machine,
   * but simplifies the API for my use. Deal with it, I shouldn't
   * have to justify it.
   */

  /* creates, fills, and binds a new vertex buffer */
  BufferIdx generateVertexBuffer(void* pData,
                                 size_t size,
                                 BufferDataUsage usage);

  void vertexBufferAttributes();

  uint32_t createShader(const std::string& vertexShader,
                        const std::string& fragmentShader);

} // namespace evolution
#endif