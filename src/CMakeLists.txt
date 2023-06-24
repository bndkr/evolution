set(${exe_name}_srcs
  main.cpp
  utils.cpp
  ShaderEditor.cpp
  ShaderEditor.hpp
  MeshManager.cpp
  MeshManager.hpp
  )
add_executable(${exe_name} ${${exe_name}_srcs})
source_group("" FILES ${${exe_name}_srcs})
target_link_libraries(${exe_name} PRIVATE ${lib_name} imgui)