set(pylib_name pyEvolution)
set(pylib_srcs bindings.cpp)
add_library(${pylib_name} MODULE ${pylib_srcs})
target_link_libraries(${pylib_name} PRIVATE EvolutionGameEngineLib Boost::python Python3::Module ${OPENGL_LIBRARY})
target_include_directories(${pylib_name} PRIVATE ${Python_INCLUDE_DIRS})
set_target_properties(${pylib_name} PROPERTIES SUFFIX ".pyd") # for windows only
set(TARGET_NAME ${pylib_name})
set(EVOLUTION_VERSION 0.1.0) # make this an actual version sometime
set(TARGET_PYMODULE_NAME ${pylib_name}.pyd)
configure_file(getwheelname.py.in getwheelname.py @ONLY)
configure_file(setup.py.in setup.py @ONLY)
execute_process(COMMAND "${Python3_EXECUTABLE}" getwheelname.py OUTPUT_VARIABLE PY_WHEELFILE
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" OUTPUT_STRIP_TRAILING_WHITESPACE)
if(PY_WHEELFILE)
    message(STATUS "Detected Python wheel filename ${PY_WHEELFILE}")
else()
    message(FATAL_ERROR "Failed to detect Python wheel filename")
endif()
add_custom_target(PyPackageBuild
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/${pylib_name}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${pylib_name}> ${CMAKE_CURRENT_BINARY_DIR}/${pylib_name}
        COMMAND "${Python3_EXECUTABLE}" -m pip wheel .
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Building python wheel package"
        USES_TERMINAL VERBATIM
        )
add_dependencies(PyPackageBuild ${pylib_name})
set_target_properties(PyPackageBuild PROPERTIES Package_Name ${PY_WHEELFILE})
add_custom_target(PyPackageInstall ALL
        COMMAND "${Python3_EXECUTABLE}" -m pip install --upgrade --force-reinstall --no-deps "${PY_WHEELFILE}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        COMMENT "Installing wheel file"
        USES_TERMINAL VERBATIM
        )
add_dependencies(PyPackageInstall PyPackageBuild)
install(TARGETS ${pylib_name} DESTINATION pyEvolution)
install(FILES example.py DESTINATION pyEvolution)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PY_WHEELFILE}" DESTINATION pyEvolution)