#ifndef EVOLUTION_TEXTURE_MANAGER
#define EVOLUTION_TEXTURE_MANAGER

#include <map>
#include <string>
#include <memory>
#include <set>

#include "Texture.hpp"

namespace evolution
{
  class TextureManager
  {
  public:
    static TextureManager* getTextureManager();
    ~TextureManager() { }

    void addTexture(const std::string& name, const std::string& filename);
    Texture* getTexture(const std::string& name);

    std::set<std::string> getAllTextures();

    // rule of three
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

  private:
    TextureManager();

    std::map<std::string, std::unique_ptr<Texture>> m_textures;

    int32_t m_maxTextureSlots;
  };

  TextureManager* getTextureManager();
} // namespace evolution

#endif