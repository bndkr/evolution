#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Buffers.hpp"
#include "ProgramSelector.hpp"
#include "Setup.hpp"
#include "Camera.hpp"
#include "MeshImporter.hpp"
#include "TextureManager.hpp"
#include "utils.hpp"
#include "Batch.hpp"

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

  std::shared_ptr<evolution::Mesh> pyCreateCubeMesh()
  {
    return std::make_shared<evolution::Mesh>(evolution::createCubeMesh());
  }

  std::shared_ptr<evolution::Mesh> pycreateTextureQuad()
  {
    return std::make_shared<evolution::Mesh>(evolution::createTextureQuad());
  }

  int pyGlfwWindowShouldClose(pyGlfwWindow window)
  {
    return glfwWindowShouldClose(window.pWindow);
  }

  struct WindowSize
  {
    int width;
    int height;
  };

  WindowSize getWindowSize(pyGlfwWindow window)
  {
    int width, height;
    glfwGetFramebufferSize(window.pWindow, &width, &height);
    return WindowSize{width, height};
  }

  void pyClearBuffer()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void pySwapBuffers(pyGlfwWindow window)
  {
    glfwSwapBuffers(window.pWindow);
  }

  void moveVector(evolution::Float3& toMove)
  {
    toMove.x += 5;
  }

} // namespace

BOOST_PYTHON_MODULE(_pyEvolution)
{
  using namespace boost::python;

  class_<pyGlfwWindow>("Window", no_init);
  class_<evolution::Float2>("Float2");
  class_<evolution::Float3>("Float3", init<float, float, float>());
  class_<evolution::Float4>("Float4");
  class_<std::shared_ptr<evolution::Mesh>>("Mesh", no_init)
    .def("draw", &evolution::Mesh::draw)
    .def("move", &evolution::Mesh::movePostion)
    .def("set_position", &evolution::Mesh::setPosition)
    .def("rotate", &evolution::Mesh::rotate)
    .def("set_rotation", &evolution::Mesh::setRotation)
    .def("assign_texture", &evolution::Mesh::assignTexture);
  class_<evolution::Camera>(
    "Camera", init<evolution::Float3, evolution::Float3, int, int>())
    .def("update_aspect", &evolution::Camera::updateWindowSize);
  class_<WindowSize>("_WindowSize")
    .def_readwrite("width", &WindowSize::width)
    .def_readwrite("height", &WindowSize::height);

  def("move_vector", &moveVector);

  def("setup", &pySetup);

  def("add_programs_from_dir", &evolution::addProgramsFromDir);
  def("add_textures_from_dir", &evolution::addTexturesFromDir);

  def("create_cube_mesh", &pyCreateCubeMesh);
  def("create_texture_quad", &pycreateTextureQuad);

  def("window_should_close", &pyGlfwWindowShouldClose);
  def("poll_events", &glfwPollEvents);
  def("update_viewport", &glViewport);
  def("get_window_size", &getWindowSize);
  def("clear_buffer", &pyClearBuffer);
  def("swap_buffers", &pySwapBuffers);
}