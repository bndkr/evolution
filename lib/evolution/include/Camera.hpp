#ifndef EVOLUTION_CAMERA_HPP
#define EVOLUTION_CAMERA_HPP

#include "Projection.hpp"

#include "Buffers.hpp" // for Float3

namespace evolution
{
  struct Mat4;

  class Camera
  {
  public:
    Camera(Float3 position, Float3 direction);

    Mat4 getEyeSpaceMatrix() const;
  private:
    PositionInfo m_position;
  };
} // namespace evolution

#endif
