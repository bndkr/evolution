#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

#include "Setup.hpp"

// #define GLEW_STATIC
// #include <GL/glew.h>
// #include <GLFW/glfw3.h>

namespace
{
  struct pyGlfwWindow
  {
    GLFWwindow* pWindow;
  };

  // helper function to return a wrapped glfwWindow object
  pyGlfwWindow pySetup(const bool enable3DMode,
                       unsigned int width,
                       unsigned int height)
  {
    return pyGlfwWindow{evolution::setup(enable3DMode, width, height)};
  }

} // namespace

BOOST_PYTHON_MODULE(_pyEvolution)
{
  using namespace boost::python;

  class_<pyGlfwWindow>("Window", no_init);

  def("_setup", &pySetup);
}