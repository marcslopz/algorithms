add_library(bracket_validator_lib "${PROJECT_SOURCE_DIR}/src/codility/bracket_validator/bracket_validator.cpp")
add_executable(
    bracket_validator
    "${PROJECT_SOURCE_DIR}/src/codility/bracket_validator/main.cpp")
target_link_libraries(bracket_validator bracket_validator_lib)
install(TARGETS bracket_validator DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_bracket_validator "${PROJECT_SOURCE_DIR}/src/codility/bracket_validator/test.cpp")
    add_test(test_bracket_validator test_bracket_validator)
    target_link_libraries(
        test_bracket_validator 
        bracket_validator_lib
        order_calculations)
endif()
