#ifndef EVOLUTION_CAMERA_HPP
#define EVOLUTION_CAMERA_HPP

#include "Projection.hpp"
#include "Buffers.hpp"

namespace evolution
{
  struct Mat4;

  class Camera
  {
  public:
    Camera(const Float3 position,
           const Float3 direction,
           const uint32_t screenWidth,
           const uint32_t screenHeight);

    Camera(const uint32_t screenWidth, const uint32_t screenHeight);

    void updateWindowSize(const uint32_t width, const uint32_t height);

    float getAspectRatio() const;

    Mat4 getEyeSpaceMatrix() const;

  private:
    PositionInfo m_position;
    uint32_t m_width;
    uint32_t m_height;
    // TODO: add fov
  };
} // namespace evolution

#endif
