#ifndef EVOLUTION_TEXTURE_HPP
#define EVOLUTION_TEXTURE_HPP

#include <string>

namespace evolution
{
  class Texture
  {
    Texture(const std::string& path);
    ~Texture();

    // delete the copy, assignment operators
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // move constructor
    Texture(Texture&& other);
    // assignment operator
    Texture& operator=(Texture&& other);

    

  };
} // namespace evolution

#endif