set(exe_name Evolution)
add_executable(${exe_name})
add_subdirectory(imgui)
add_subdirectory(color_console)
set(${exe_name}_srcs
  Render.cpp
  Render.hpp
  Buffers.cpp
  Buffers.hpp
  main.cpp
  utils.cpp
)
target_include_directories(${exe_name} PUBLIC ${GLFW3_INCLUDE_DIR})
target_include_directories(${exe_name} PUBLIC ${GLEW_INCLUDE_DIR})
target_link_libraries(${exe_name} ${GLFW3_LIBRARY})
target_link_libraries(${exe_name} ${GLEW_LIBRARY})
source_group("" FILES ${${exe_name}_srcs})
target_sources(${exe_name} PUBLIC ${${exe_name}_srcs})