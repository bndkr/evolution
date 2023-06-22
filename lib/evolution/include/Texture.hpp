#ifndef EVOLUTION_TEXTURE_HPP
#define EVOLUTION_TEXTURE_HPP

#include <string>

namespace evolution
{
  class Texture
  {
  public:
    /* Create a texture object.
     * @param[in] path - the file path to a texture image on disk
     * @param[in] slot - the texture slot to insert the texture
     * @param[in] name - the name of the texture. This is also used as
     * the name of the associated sampler in a shader uniform.
     */
    Texture(const std::string& path, uint32_t slot, const std::string& name);
    ~Texture();

    // delete the copy, assignment operators
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // move constructor
    Texture(Texture&& other);
    // assignment operator
    Texture& operator=(Texture&& other);

    int32_t getSlotNum() const;
    std::string getName() const;

  private:
    uint32_t m_texId;
    int32_t m_slot;
    std::string m_name;
    void release();
  };
} // namespace evolution

#endif