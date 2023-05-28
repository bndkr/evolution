#ifndef EVOLUTION_PROJECTION_HPP
#define EVOLUTION_PROJECTION_HPP

namespace evolution
{
  struct Mat4
  {
    float m[16];
  };

  void rotateAroundX(Mat4& matrix, const float theta);
  void rotateAroundY(Mat4& matrix, const float theta);
  void rotateAroundZ(Mat4& matrix, const float theta);
  void scaleMatrix(Mat4& matrix, const float x, const float y, const float z);
} // namespace evolution

#endif