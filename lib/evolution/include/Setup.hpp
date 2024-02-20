#ifndef EVOLUTION_SETUP_HPP
#define EVOLUTION_SETUP_HPP

#include "Input.hpp"

struct GLFWwindow;

namespace evolution
{
  GLFWwindow* setup(const bool enable3DMode,
                    const unsigned int width,
                    const unsigned int height);

  InputManager* getInputManager(GLFWwindow* window);
  
} // namespace evolution
#endif