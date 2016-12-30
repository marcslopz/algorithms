add_library(light_chains_lib "${PROJECT_SOURCE_DIR}/src/codility/light_chains/light_chains.cpp")
add_executable(
    light_chains
    "${PROJECT_SOURCE_DIR}/src/codility/light_chains/main.cpp")
target_link_libraries(light_chains light_chains_lib)
install(TARGETS light_chains DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_light_chains "${PROJECT_SOURCE_DIR}/src/codility/light_chains/test.cpp")
    add_test(test_light_chains test_light_chains)
    target_link_libraries(
        test_light_chains 
        light_chains_lib
        order_calculations)
endif()
