add_library(cyclic_rotation_lib "${PROJECT_SOURCE_DIR}/src/codility/lessons/cyclic_rotation/cyclic_rotation.cpp")
add_executable(
    cyclic_rotation
    "${PROJECT_SOURCE_DIR}/src/codility/lessons/cyclic_rotation/main.cpp")
target_link_libraries(cyclic_rotation cyclic_rotation_lib)
install(TARGETS cyclic_rotation DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_cyclic_rotation "${PROJECT_SOURCE_DIR}/src/codility/lessons/cyclic_rotation/test.cpp")
    add_test(test_cyclic_rotation test_cyclic_rotation)
    target_link_libraries(
        test_cyclic_rotation 
        cyclic_rotation_lib
        order_calculations)
endif()
