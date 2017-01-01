add_library(tape_equilibrium_lib "${PROJECT_SOURCE_DIR}/src/codility/lessons/tape_equilibrium/tape_equilibrium.cpp")
add_executable(
    tape_equilibrium
    "${PROJECT_SOURCE_DIR}/src/codility/lessons/tape_equilibrium/main.cpp")
target_link_libraries(tape_equilibrium tape_equilibrium_lib)
install(TARGETS tape_equilibrium DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_tape_equilibrium "${PROJECT_SOURCE_DIR}/src/codility/lessons/tape_equilibrium/test.cpp")
    add_test(test_tape_equilibrium test_tape_equilibrium)
    target_link_libraries(
        test_tape_equilibrium 
        tape_equilibrium_lib
        order_calculations)
endif()
