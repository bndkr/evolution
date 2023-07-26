#define BOOST_PYTHON_STATIC_LIB
#include <boost/python.hpp>

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

} // namespace

BOOST_PYTHON_MODULE(_pyEvolution)
{
  using namespace boost::python;

  class_<pyGlfwWindow>("Window", no_init);
  class_<evolution::Float2>("Float2");
  class_<evolution::Float3>("Float3");
  class_<evolution::Float4>("Float4");
  class_<std::shared_ptr<evolution::Mesh>>("Mesh", no_init);


  def("setup", &pySetup);

  def("add_programs_from_dir", &evolution::addProgramsFromDir);
  def("add_textures_from_dir", &evolution::addTexturesFromDir);

  def("create_cube_mesh", &pyCreateCubeMesh);
  def("create_texture_quad", &pycreateTextureQuad);
}