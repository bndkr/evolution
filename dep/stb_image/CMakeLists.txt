set(stb_image_srcs
  include/stb_image/stb_image.h
)
add_library(stb_image INTERFACE ${stb_image_srcs})
target_include_directories(stb_image INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
source_group("" FILES ${stb_image_srcs})
xpSourceListAppend("${stb_image_srcs}")