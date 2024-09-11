set(pylib_name pyEvolution)
set(pylib_srcs bindings.cpp)
add_library(${pylib_name} MODULE ${pylib_srcs})
target_link_libraries(${pylib_name} PRIVATE EvolutionGameEngineLib Boost::python Python::Module ${OPENGL_LIBRARY})
target_include_directories(${pylib_name} PRIVATE ${Python_INCLUDE_DIRS})
set_target_properties(${pylib_name} PROPERTIES SUFFIX ".pyd") # for windows only
set(TARGET_NAME ${pylib_name})
set(EVOLUTION_VERSION 0.1.0) # make this an actual version sometime
set(TARGET_PYMODULE_NAME ${pylib_name})
configure_file(getwheelname.py.in getwheelname.py @ONLY)
configure_file(setup.py.in setup.py @ONLY)

execute_process(COMMAND "${PYTHON_EXECUTABLE}" getwheelname.py OUTPUT_VARIABLE PY_WHEELFILE
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "Detected Python wheel filename ${PY_WHEELFILE}")
install(TARGETS ${pylib_name} DESTINATION pyEvolution)
install(FILES example.py DESTINATION pyEvolution)
