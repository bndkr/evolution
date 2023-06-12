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
    : m_width(screenWidth), m_height(screenHeight)
  {
    m_position.position = Float3{0.f, 0.f, 0.f};
    m_position.rotation = Float3{0.f, 0.f, 0.f};
    ;
  }

  void Camera::updateWindowSize(const uint32_t width, const uint32_t height)
  {
    m_width = width;
    m_height = height;
  }

  float Camera::getAspectRatio() const
  {
    return (float)m_width / (float)m_height;
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
