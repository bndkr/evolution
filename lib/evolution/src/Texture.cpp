#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>

namespace evolution
{
  Texture::Texture(const std::string& path,
                   const std::string& name)
    : m_texId(0), m_name(name)
  {
    int width, height, numChannels;
    stbi_set_flip_vertically_on_load(true);
    uint8_t* data = stbi_load(path.c_str(), &width, &height, &numChannels, 0);
    if (!data)
    {
      throw std::runtime_error("could not load file: " + path);
    }
    glGenTextures(1, &m_texId);
    glBindTexture(GL_TEXTURE_2D, m_texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 numChannels == 4 ? GL_RGBA : GL_RGB,
                 width,
                 height,
                 0,
                 numChannels == 4 ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  Texture::Texture(Texture&& other)
    : m_texId(other.m_texId), m_name(other.m_name)
  {
    other.m_texId = 0;
  }

  std::string Texture::getName() const
  {
    return m_name;
  }

  uint32_t Texture::getId() const
  {
    return m_texId;
  }

  Texture& Texture::operator=(Texture&& other)
  {
    if (this != &other)
    {
      release();
      std::swap(m_texId, other.m_texId);
      std::swap(m_name, other.m_name);
    }
    return other;
  }
  void Texture::release()
  {
    glDeleteTextures(1, &m_texId);
    m_texId = 0;
  }

  Texture::~Texture()
  {
    release();
  }
} // namespace evolution
