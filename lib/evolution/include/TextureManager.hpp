#ifndef EVOLUTION_TEXTURE_MANAGER
#define EVOLUTION_TEXTURE_MANAGER

#include "Texture.hpp"

#include <boost/filesystem.hpp>

#include <map>
#include <string>
#include <memory>
#include <set>

namespace evolution
{
  class TextureManager
  {
  public:
    static TextureManager* getTextureManager();
    ~TextureManager() { }

    void addTexture(const std::string& name, const std::string& filename);
    void addTexture(const std::string& name,
                    const boost::filesystem::path& filename);

    Texture* getTexture(const std::string& name);

    std::set<std::string> getAllTextures();

    // rule of three
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

  private:
    TextureManager();

    std::map<std::string, std::shared_ptr<Texture>> m_textures;

    int32_t m_maxTextureSlots;
  };

  TextureManager* getTextureManager();
} // namespace evolution

#endif