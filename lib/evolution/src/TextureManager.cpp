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
    m_textures[name] =
      std::make_shared<Texture>(Texture(filename, name));
  }

  void TextureManager::addTexture(const std::string& name,
                                  const boost::filesystem::path& filename)
  {
    addTexture(name, filename.string());
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
