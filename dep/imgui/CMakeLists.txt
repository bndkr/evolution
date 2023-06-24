set(imgui_srcs
  include/imgui/imconfig.h
  include/imgui/imgui.h
  include/imgui/imgui_impl_glfw.h
  include/imgui/imgui_impl_opengl3.h
  include/imgui/imgui_impl_opengl3_loader.h
  include/imgui/imgui_internal.h
  include/imgui/imstb_rectpack.h
  include/imgui/imstb_textedit.h
  include/imgui/imstb_truetype.h
  include/imgui/imgui_stdlib.h
  src/imgui.cpp
  src/imgui_demo.cpp
  src/imgui_draw.cpp
  src/imgui_impl_glfw.cpp
  src/imgui_impl_opengl3.cpp
  src/imgui_tables.cpp
  src/imgui_widgets.cpp
  src/imgui_stdlib.cpp
)
add_library(imgui STATIC ${imgui_srcs})
source_group("" FILES ${imgui_srcs})
target_include_directories(imgui PUBLIC ${GLFW3_INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(
  imgui
  PRIVATE
  ${OPENGL_LIBRARY}
  ${GLFW3_LIBRARY}
)