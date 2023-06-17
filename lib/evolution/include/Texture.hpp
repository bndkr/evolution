#ifndef EVOLUTION_TEXTURE_HPP
#define EVOLUTION_TEXTURE_HPP

#include <string>

namespace evolution
{
  class Texture
  {
  public:
    Texture(const std::string& path);
    ~Texture();

    // delete the copy, assignment operators
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // move constructor
    Texture(Texture&& other);
    // assignment operator
    Texture& operator=(Texture&& other);

  private:
    uint32_t m_texId;
  };
} // namespace evolution

#endif