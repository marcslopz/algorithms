add_library(binary_gap_lib "${PROJECT_SOURCE_DIR}/src/codility/binary_gap/binary_gap.cpp")
add_executable(
    binary_gap
    "${PROJECT_SOURCE_DIR}/src/codility/binary_gap/main.cpp")
target_link_libraries(binary_gap binary_gap_lib)
install(TARGETS binary_gap DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_binary_gap "${PROJECT_SOURCE_DIR}/src/codility/binary_gap/test.cpp")
    add_test(test_binary_gap test_binary_gap)
    target_link_libraries(
        test_binary_gap 
        binary_gap_lib
        order_calculations)
endif()
