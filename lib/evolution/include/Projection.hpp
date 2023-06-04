#ifndef EVOLUTION_PROJECTION_HPP
#define EVOLUTION_PROJECTION_HPP

namespace evolution
{
  // row-major matrix representation
  struct Mat4
  {
    float m[16];
  };

  // Returns an identity matrix of type Mat4
  Mat4 identityMatrix();

  // Multiplies two transformation matrices and stores the result in mat1
  void multiplyTransformationMatrices(Mat4& mat1, Mat4& mat2);

  // Rotates the given matrix around the X-axis by the specified angle (in
  // radians)
  void rotateAroundX(Mat4& matrix, const float theta);

  // Rotates the given matrix around the Y-axis by the specified angle (in
  // radians)
  void rotateAroundY(Mat4& matrix, const float theta);

  // Rotates the given matrix around the Z-axis by the specified angle (in
  // radians)
  void rotateAroundZ(Mat4& matrix, const float theta);

  // Scales the given matrix by the specified factors in each dimension
  void scaleMatrix(Mat4& matrix, const float x, const float y, const float z);

  // Translates the given matrix by an offset
  void translateMatrix(Mat4& matrix,
                       const float x,
                       const float y,
                       const float z);

  Mat4 getProjectionMatrix(const float fovy,
                           const float aspectRatio,
                           const float nearPlane,
                           const float farPlane);
} // namespace evolution

#endif