set(lib_name ${project_name}Lib)
set(${lib_name}_srcs
  include/Buffers.hpp
  include/Projection.hpp
  include/Setup.hpp
  include/Engine.hpp
  include/Shader.hpp
  include/Camera.hpp
  include/Input.hpp
  include/ProgramSelector.hpp
  include/MeshImporter.hpp
  include/Texture.hpp
  include/TextureManager.hpp
  include/utils.hpp
  include/Batch.hpp
  src/Buffers.cpp
  src/Projection.cpp
  src/Setup.cpp
  src/Engine.cpp
  src/Shader.cpp
  src/Camera.cpp
  src/Input.cpp
  src/ProgramSelector.cpp
  src/MeshImporter.cpp
  src/Texture.cpp
  src/TextureManager.cpp
  src/utils.cpp
  src/Batch.cpp
)
add_library(${lib_name} STATIC ${${lib_name}_srcs})
source_group("" FILES ${${lib_name}_srcs})
target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
  ${lib_name}
  PUBLIC
  GLEW::glew_s
  glfw
  PRIVATE
  Boost::filesystem
  assimp
  color_console
  eigen
  stb_image
)
add_subdirectory(test)
