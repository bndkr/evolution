set(${exe_name}_srcs
  main.cpp
  utils.cpp
  MeshManager.cpp
  MeshManager.hpp
  CameraControls.cpp
  CameraControls.hpp
  )
add_executable(${exe_name} ${${exe_name}_srcs})
source_group("" FILES ${${exe_name}_srcs})
target_link_libraries(${exe_name} PRIVATE ${lib_name} imgui Boost::filesystem)
install(TARGETS ${exe_name})
install(DIRECTORY assets DESTINATION .)
install(DIRECTORY shaders DESTINATION .)