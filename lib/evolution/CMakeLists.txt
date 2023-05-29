set(${lib_name}_srcs
  include/Render.hpp
  include/Buffers.hpp
  include/Projection.hpp
  include/Setup.hpp
  include/Engine.hpp
  src/Render.cpp
  src/Buffers.cpp
  src/Projection.cpp
  src/Setup.cpp
  src/Engine.cpp
)
add_library(${lib_name} STATIC ${${lib_name}_srcs})
source_group("" FILES ${${lib_name}_srcs})
xpFindPkg(PKGS eigen glew)
set(GLFW3_INCLUDE_DIR "C:/dev/extern/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/include" CACHE PATH "path of GLFW3 include")
set(GLFW3_LIB "C:/dev/extern/glfw-3.3.8.bin.WIN64/glfw-3.3.8.bin.WIN64/lib-vc2019/glfw3_mt.lib" CACHE PATH "path of GLFW3 lib")
target_include_directories(${lib_name} PUBLIC ${GLFW3_INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)
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
xpSourceListAppend("${${lib_name}_srcs}")
