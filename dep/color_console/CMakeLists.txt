set(color_console_srcs
  include/color_console/color.hpp
)
add_library(color_console INTERFACE ${color_console_srcs})
target_include_directories(color_console INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
source_group("" FILES ${color_console_srcs})