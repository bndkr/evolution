set(exe_name Evolution)
add_executable(${exe_name})
add_subdirectory(imgui)
add_subdirectory(color_console)
set(${exe_name}_srcs
  Render.cpp
  Render.hpp
  Buffers.cpp
  Buffers.hpp
  Projection.cpp
  Projection.hpp
  main.cpp
  utils.cpp
)
source_group("" FILES ${${exe_name}_srcs})
target_sources(${exe_name} PUBLIC ${${exe_name}_srcs})
xpFindPkg(PKGS eigen glew)
target_include_directories(${exe_name} PRIVATE ${GLFW3_INCLUDE_DIR})
target_link_libraries(${exe_name} PRIVATE ${OPENGL_LIBRARY}  ${GLFW3_LIBRARY} Eigen3::Eigen GLEW::glew_s)
xpSourceListAppend("${${exe_name}_srcs}")