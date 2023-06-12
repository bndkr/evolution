#include "Camera.hpp"
#include "Projection.hpp"

namespace evolution
{
  Camera::Camera(Float3 position,
                 Float3 direction,
                 const uint32_t screenWidth,
                 const uint32_t screenHeight)
    : m_width(screenWidth), m_height(screenHeight)
  {
    m_position.position = position;
    m_position.rotation = direction;
  }

  Camera::Camera(const uint32_t screenWidth, const uint32_t screenHeight)
  {
    Camera({0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, screenWidth, screenHeight);
  }

  Mat4 Camera::getEyeSpaceMatrix() const
  {
    auto mat = identityMatrix();
    // rotate matrix
    translateMatrix(
      mat, m_position.position.x, m_position.position.y, m_position.position.z);
    return mat;
  }
} // namespace evolution
