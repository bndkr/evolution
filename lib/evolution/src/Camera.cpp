#include "Camera.hpp"
#include "Projection.hpp"

namespace evolution
{
  Camera::Camera(Float3 position, Float3 direction)
  {
    m_position.position = position;
    m_position.rotation = direction;
  }

  Mat4 Camera::getEyeSpaceMatrix() const
  {
    auto mat = identityMatrix();
    // rotate matrix
    translateMatrix(mat,
                    m_position.position.x,
                    m_position.position.y,
                    m_position.position.z);
    return mat;
  }
} // namespace evolution
