set(test_name ${lib_name}Test)
set(${test_name}_srcs
  EvolutionGameEngineTestMain.cpp
)
add_executable(${test_name} ${${test_name}_srcs})
target_link_libraries(${test_name} PRIVATE Boost::unit_test_framework EvolutionGameEngineLib)
# test exe breaks without this next line
# set_target_properties(${test_name} PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_test(NAME ${test_name} COMMAND ${test_name})