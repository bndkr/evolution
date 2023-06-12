#ifndef EVOLUTION_SETUP_HPP
#define EVOLUTION_SETUP_HPP

struct GLFWwindow;

namespace evolution
{
  GLFWwindow* setup(const bool enable3DMode,
                    unsigned int width,
                    unsigned int height);
} // namespace evolution
#endif