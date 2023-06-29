#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "utils.hpp"

void createImage()
{
  // create image
  typedef uint8_t byte;
  const int imageHeight = 512;
  const int imageWidth = 1024;

  byte* imageBuffer = new byte[imageHeight * imageWidth * 4]{};
  for (uint32_t y = 0; y < imageHeight; y++)
  {
    for (uint32_t x = 0; x < imageWidth * 4; x += 4)
    {
      imageBuffer[y * (imageWidth * 4) + x] = 0;
      imageBuffer[y * (imageWidth * 4) + x + 1] = 255;
      imageBuffer[y * (imageWidth * 4) + x + 2] = 255;
      imageBuffer[y * (imageWidth * 4) + x + 3] = 255;
    }
  }
  // create a texture
  GLuint textureID = 0;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA8,
               imageWidth,
               imageHeight,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               imageBuffer);
}
