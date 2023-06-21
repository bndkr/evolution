#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TextureManager.hpp"

namespace evolution
{
  TextureManager::TextureManager()
  {
    m_currTextureSlot = 0;
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextureSlots);
  }

  TextureManager* TextureManager::getTextureManager()
  {
    static TextureManager object;
    return &object;
  }

  void TextureManager::addTexture(const std::string& name,
                                  const Texture& texture)
  {
    if (m_currTextureSlot < m_maxTextureSlots)
    {
      m_textures[name] = std::make_unique<Texture>(texture);
      m_currTextureSlot++;
    }
    else // we've run out of texture slots...
    {
      throw std::runtime_error(
        "not implemented yet. we've run out of texture slots.");
    }
  }

  Texture* TextureManager::getTexture(const std::string& name)
  {
    if (m_textures.count(name))
    {
      return m_textures[name].get();
    }
    return nullptr;
  }

  std::set<std::string> TextureManager::getAllTextures()
  {
    std::set<std::string> result;
    for (const auto& item : m_textures)
    {
      result.insert(item.first);
    }
    return result;
  }
} // namespace evolution
