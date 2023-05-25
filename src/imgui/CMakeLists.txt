set(imgui_srcs
  imconfig.h
  imgui.cpp
  imgui.h
  imgui_demo.cpp
  imgui_draw.cpp
  imgui_impl_glfw.cpp
  imgui_impl_glfw.h
  imgui_impl_opengl3.cpp
  imgui_impl_opengl3.h
  imgui_impl_opengl3_loader.h
  imgui_internal.h
  imgui_tables.cpp
  imgui_widgets.cpp
  imstb_rectpack.h
  imstb_textedit.h
  imstb_truetype.h
)
target_sources(${exe_name} PUBLIC ${imgui_srcs})
source_group("imgui" FILES ${imgui_srcs})
xpSourceListAppend("${imgui_srcs}")