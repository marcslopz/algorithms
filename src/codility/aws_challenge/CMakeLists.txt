add_library(aws_challenge_lib "${PROJECT_SOURCE_DIR}/src/codility/aws_challenge/aws_challenge.cpp")
add_executable(
    aws_challenge
    "${PROJECT_SOURCE_DIR}/src/codility/aws_challenge/main.cpp")
target_link_libraries(aws_challenge aws_challenge_lib)
install(TARGETS aws_challenge DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_aws_challenge "${PROJECT_SOURCE_DIR}/src/codility/aws_challenge/test.cpp")
    add_test(test_aws_challenge test_aws_challenge)
    target_link_libraries(
        test_aws_challenge 
        aws_challenge_lib
        order_calculations)
endif()
