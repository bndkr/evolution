#define BOOST_TEST_MODULE EvolutionGameEngineLibTest
#include <boost/test/unit_test.hpp>

#include "Projection.hpp"

using namespace evolution;

namespace
{
  void checkMatrixEquivalence(const Mat4& lhs, const Mat4& rhs)
  {
    for (int i = 0; i < 16; i++)
    {
      BOOST_CHECK_EQUAL(lhs.m[i], rhs.m[i]);
    }
  }
} // namespace

BOOST_AUTO_TEST_CASE(IdentityMatrixTest)
{
  // clang-format off
  Mat4 knownIdentityMatrix = {
    {1.0f, 0.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f, 0.0f,
     0.0f, 0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 0.0f, 1.0f}
  };
  // clang-format on
  checkMatrixEquivalence(identityMatrix(), knownIdentityMatrix);
}

BOOST_AUTO_TEST_CASE(MatrixMultiplicationTest)
{
  // clang-format off
  Mat4 mat1 = {
    1.0f, 2.0f, 3.0f, 4.0f,
    5.0f, 6.0f, 7.0f, 8.0f,
    9.0f, 10.0f, 11.0f, 12.0f,
    13.0f, 14.0f, 15.0f, 16.0f
  };

  Mat4 mat2 = {
    17.0f, 18.0f, 19.0f, 20.0f,
    21.0f, 22.0f, 23.0f, 24.0f,
    25.0f, 26.0f, 27.0f, 28.0f,
    29.0f, 30.0f, 31.0f, 32.0f
  };

  Mat4 expected = {
    250.0f, 260.0f, 270.0f, 280.0f,
    618.0f, 644.0f, 670.0f, 696.0f,
    986.0f, 1028.0f, 1070.0f, 1112.0f,
    1354.0f, 1412.0f, 1470.0f, 1528.0f
  };
  // clang-format on

  multiplyTransformationMatrices(mat2, mat1);

  checkMatrixEquivalence(mat2, expected);
}

BOOST_AUTO_TEST_CASE(testScaleMatrix)
{
  // clang-format off
  Mat4 m = {
    1.0f, 2.0f, 3.0f, 4.0f,
    2.0f, 3.0f, 4.0f, 1.0f,
    3.0f, 4.0f, 1.0f, 2.0f,
    4.0f, 1.0f, 2.0f, 3.0f,
  };
  // clang-format on
  float x = 2.0f;
  float y = 2.0f;
  float z = 2.0f;

  // clang-format off
  Mat4 expected = {
    2.0f, 4.0f, 6.0f, 8.0f,
    4.0f, 6.0f, 8.0f, 2.0f,
    6.0f, 8.0f, 2.0f, 4.0f,
    4.0f, 1.0f, 2.0f, 3.0f
  };
  // clang-format on

  scaleMatrix(m, x, y, z);
  checkMatrixEquivalence(m, expected);
}

BOOST_AUTO_TEST_CASE(testTranslateMatrix)
{
  // clang-format off
  Mat4 m = {
    1.0f, 2.0f, 3.0f, 4.0f,
    2.0f, 3.0f, 4.0f, 1.0f,
    3.0f, 4.0f, 1.0f, 2.0f,
    4.0f, 1.0f, 2.0f, 3.0f,
  };
  Mat4 expected = {
    1.0f,  2.0f, 3.0f,  4.0f,
    14.0f, 6.0f, 10.0f, 10.0f,
    3.0f,  4.0f, 1.0f,  2.0f,
    4.0f,  1.0f, 2.0f,  3.0f,
  };
  // clang-format on

  float x = 0.0f;
  float y = 3.0f;
  float z = 0.0f;

  translateMatrix(m, x, y, z);
  checkMatrixEquivalence(m, expected);
}