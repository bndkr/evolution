cmake_minimum_required(VERSION 3.21)
project(evolution)
#################################
find_package(OpenGL REQUIRED)
set(GLEW_USE_STATIC_LIBS TRUE)
set(GLEW_INSTALL_DIR "C:/dev/extern/glew-2.1.0" CACHE FILEPATH "Path to GLEW installation" FORCE)
set(CMAKE_PREFIX_PATH ${GLEW_INSTALL_DIR})
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/dist CACHE PATH "installation path" FORCE)
endif()
find_package(Boost REQUIRED COMPONENTS unit_test_framework filesystem python PATHS C:/Boost)
find_package(Python3 REQUIRED COMPONENTS Interpreter Development.Module)
find_package(GLEW REQUIRED)
################################
# dependency order
add_subdirectory(dep)
set(project_name EvolutionGameEngine)
set(BUILD_SHARED_LIBS OFF) # build assimp as static library
add_subdirectory(dep/assimp EXCLUDE_FROM_ALL)
add_subdirectory(dep/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib)
add_subdirectory(example)
add_subdirectory(python)
