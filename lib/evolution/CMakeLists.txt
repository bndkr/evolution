set(${lib_name}_srcs
  include/Buffers.hpp
  include/Projection.hpp
  include/Setup.hpp
  include/Engine.hpp
  include/Shader.hpp
  include/Camera.hpp
  src/Buffers.cpp
  src/Projection.cpp
  src/Setup.cpp
  src/Engine.cpp
  src/Shader.cpp
  src/Camera.cpp
)
add_library(${lib_name} STATIC ${${lib_name}_srcs})
source_group("" FILES ${${lib_name}_srcs})
xpFindPkg(PKGS eigen glew)
set(GLFW3_INCLUDE_DIR "${GLFW3_ROOT}/include" CACHE PATH "path of GLFW3 include dir")
set(GLFW3_LIB "${GLFW3_ROOT}/lib/glfw3_mt.lib" CACHE PATH "path of GLFW3 lib")
target_include_directories(
  ${lib_name}
  PUBLIC
  ${GLFW3_INCLUDE_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
  ${lib_name}
  PUBLIC
  # ${OPENGL_LIBRARY}
  GLEW::glew_s
  ${GLFW3_LIB}
  PRIVATE
  color_console
  Eigen3::Eigen
)
add_subdirectory(test)
xpSourceListAppend("${${lib_name}_srcs}")
