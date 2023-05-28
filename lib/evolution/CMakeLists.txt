set(${lib_name}_srcs
  include/Render.hpp
  include/Buffers.hpp
  include/Projection.hpp
  include/Setup.hpp
  src/Render.cpp
  src/Buffers.cpp
  src/Projection.cpp
  src/Setup.cpp
)
add_library(${lib_name} STATIC ${${lib_name}_srcs})
source_group("" FILES ${${lib_name}_srcs})
xpFindPkg(PKGS eigen glew)
target_include_directories(${lib_name} PUBLIC ${GLFW3_INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
  ${lib_name}
  PUBLIC
  ${OPENGL_LIBRARY}
  GLEW::glew_s
  ${GLFW3_LIBRARY}
  imgui
  PRIVATE
  color_console
  Eigen3::Eigen
)
xpSourceListAppend("${${lib_name}_srcs}")
