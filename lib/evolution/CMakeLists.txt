set(${lib_name}_srcs
  include/Buffers.hpp
  include/Projection.hpp
  include/Setup.hpp
  include/Engine.hpp
  include/Shader.hpp
  include/Camera.hpp
  include/ProgramSelector.hpp
  include/MeshImporter.hpp
  include/Texture.hpp
  include/TextureManager.hpp
  include/utils.hpp
  src/Buffers.cpp
  src/Projection.cpp
  src/Setup.cpp
  src/Engine.cpp
  src/Shader.cpp
  src/Camera.cpp
  src/ProgramSelector.cpp
  src/MeshImporter.cpp
  src/Texture.cpp
  src/TextureManager.cpp
  src/utils.cpp
)
add_library(${lib_name} STATIC ${${lib_name}_srcs})
source_group("" FILES ${${lib_name}_srcs})
set(GLFW3_INCLUDE_DIR "${GLFW3_ROOT}/include" CACHE PATH "path of GLFW3 include dir")
set(GLFW3_LIB "${GLFW3_ROOT}/lib/glfw3.lib" CACHE PATH "path of GLFW3 lib")
set(ASSIMP_DIR "C:/Program Files (x86)/Assimp")
set(ASSIMP_INCLUDE_DIR "${ASSIMP_DIR}/include")
# we'll link the debug libs for now. make sure to switch this when performance is relevant.
set(ASSIMP_LIB
#  "${ASSIMP_DIR}/lib/assimp-vc143-mt.lib"
  "${ASSIMP_DIR}/lib/assimp-vc143-mtd.lib"
#  "${ASSIMP_DIR}/lib/zlibstatic.lib"
  "${ASSIMP_DIR}/lib/zlibstaticd.lib"
)
target_include_directories(
  ${lib_name}
  PUBLIC
  ${GLFW3_INCLUDE_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${ASSIMP_INCLUDE_DIR}
)
target_link_libraries(
  ${lib_name}
  PUBLIC
  GLEW::glew_s
  ${GLFW3_LIB}
  PRIVATE
  Boost::filesystem
  ${ASSIMP_LIB}
  color_console
  eigen
  stb_image
)
add_subdirectory(test)
