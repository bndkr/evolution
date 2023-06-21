#include <stdexcept>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "TextureManager.hpp"

namespace evolution
{
  TextureManager::TextureManager()
  {
    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &m_maxTextureSlots);
  }

  TextureManager* TextureManager::getTextureManager()
  {
    static TextureManager object;
    return &object;
  }

  void TextureManager::addTexture(const std::string& name,
                                  const std::string& filename)
  {
    // keep track of the current texture slot so each
    // texture has its own slot.
    static int32_t currTextureSlot = 0;

    if (currTextureSlot < m_maxTextureSlots)
    {
      m_textures[name] =
        std::make_unique<Texture>(Texture(filename, currTextureSlot, name));
      currTextureSlot++;
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

  TextureManager* getTextureManager()
  {
    return TextureManager::getTextureManager();
  }
} // namespace evolution
