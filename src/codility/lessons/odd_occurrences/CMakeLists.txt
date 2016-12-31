add_library(odd_occurrences_lib "${PROJECT_SOURCE_DIR}/src/codility/lessons/odd_occurrences/odd_occurrences.cpp")
add_executable(
    odd_occurrences
    "${PROJECT_SOURCE_DIR}/src/codility/lessons/odd_occurrences/main.cpp")
target_link_libraries(odd_occurrences odd_occurrences_lib)
install(TARGETS odd_occurrences DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_odd_occurrences "${PROJECT_SOURCE_DIR}/src/codility/lessons/odd_occurrences/test.cpp")
    add_test(test_odd_occurrences test_odd_occurrences)
    target_link_libraries(
        test_odd_occurrences 
        odd_occurrences_lib
        order_calculations)
endif()
