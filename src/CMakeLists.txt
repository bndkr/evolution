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