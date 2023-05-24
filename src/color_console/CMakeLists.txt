set(color_console_srcs
  color.hpp
)
target_sources(${exe_name} PUBLIC ${color_console_srcs})
source_group("color_console" FILES ${color_console_srcs})