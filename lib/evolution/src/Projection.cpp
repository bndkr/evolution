#include "Projection.hpp"

#include <eigen3/Eigen/Dense>

namespace
{
  typedef Eigen::Matrix4f Matrix;

  evolution::Mat4 getRotationMatrix(char axis, float theta)
  {
    auto c = cos(theta);
    auto s = sin(theta);
    Matrix mat = Matrix::Zero();
    switch (axis)
    {
    case 'x':
      mat(0, 0) = 1;
      mat(1, 1) = c;
      mat(1, 2) = -s;
      mat(2, 1) = s;
      mat(2, 2) = -c;
      mat(3, 3) = 1;
      break;
    case 'y':
      mat(0, 0) = c;
      mat(0, 2) = s;
      mat(1, 1) = 1;
      mat(2, 0) = -s;
      mat(2, 2) = c;
      mat(3, 3) = 1;
      break;
    case 'z':
      mat(0, 0) = c;
      mat(0, 1) = -s;
      mat(1, 0) = s;
      mat(1, 1) = c;
      mat(2, 2) = 1;
      mat(3, 3) = 1;
      break;
    }
    evolution::Mat4 res;
    std::memcpy(res.m, mat.data(), sizeof(res));
    return res;
  }
} // namespace

namespace evolution
{
  Mat4 identityMatrix()
  {
    Matrix m = Matrix::Identity();
    Mat4 res;
    std::memcpy(res.m, m.data(), sizeof(res));
    return res;
  }

  void multiplyTransformationMatrices(Mat4& mat1, Mat4& mat2)
  {
    Matrix m1 = Eigen::Map<Matrix>(mat1.m);
    Matrix m2 = Eigen::Map<Matrix>(mat2.m);
    Matrix result = m2 * m1;
    std::memcpy(mat1.m, result.data(), sizeof(mat1));
  }

  void rotateAroundX(Mat4& matrix, const float theta)
  {
    auto rotationMatrix = getRotationMatrix('x', theta);
    multiplyTransformationMatrices(matrix, rotationMatrix);
  }

  void rotateAroundY(Mat4& matrix, const float theta)
  {
    auto rotationMatrix = getRotationMatrix('y', theta);
    multiplyTransformationMatrices(matrix, rotationMatrix);
  }

  void rotateAroundZ(Mat4& matrix, const float theta)
  {
    auto rotationMatrix = getRotationMatrix('z', theta);
    multiplyTransformationMatrices(matrix, rotationMatrix);
  }

  void scaleMatrix(Mat4& matrix, const float x, const float y, const float z) {
    // clang-format off
    Mat4 scaleMatrix = {
      x, 0.0f, 0.0f, 0.0f,
      0.0f, y, 0.0f, 0.0f,
      0.0f, 0.0f, z, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };
    // clang-format on

    multiplyTransformationMatrices(matrix, scaleMatrix);
  }
} // namespace evolution
