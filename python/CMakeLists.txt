set(pylib_name pyEvolution)
set(pylib_srcs bindings.cpp)
add_library(${pylib_name} SHARED ${pylib_srcs})
target_link_libraries(${pylib_name} PRIVATE ${lib_name} Boost::python Python::Module)
target_include_directories(${pylib_name} PRIVATE ${Python_INCLUDE_DIRS})
set_target_properties(${pylib_name} PROPERTIES SUFFIX ".pyd") # for windows only
install(TARGETS ${pylib_name} DESTINATION pyEvolution)
