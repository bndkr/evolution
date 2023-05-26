#include "Projection.hpp"
#include <eigen3/Eigen/Dense>

namespace
{
  typedef Eigen::Matrix4f Matrix;
}

namespace evolution
{
  void rotateAroundX(Mat4& matrix, const float theta)
  {
    Matrix rotationMat;
    // clang-format off
    rotationMat << 1,          0,           0, 0,
                   0, cos(theta), -sin(theta), 0,
                   0, sin(theta),  cos(theta), 0,
                   0,          0,           0, 1;
    // clang-format on
    Matrix m = Eigen::Map<Matrix>(matrix.m);
    m = m * rotationMat;
    std::memcpy(matrix.m, m.data(), sizeof(matrix));
  }

  void rotateAroundY(Mat4& matrix, const float theta) {}

  void rotateAroundZ(Mat4& matrix, const float theta) {}

  void scaleMatrix(Mat4& matrix, const float x, const float y, const float z) {}
} // namespace evolution
