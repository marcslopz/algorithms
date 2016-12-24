add_library(max_pairwise_product_lib "${PROJECT_SOURCE_DIR}/src/max_pairwise_product/max_pairwise_product.cpp")
add_executable(
    max_pairwise_product
    "${PROJECT_SOURCE_DIR}/src/max_pairwise_product/main.cpp")
target_link_libraries(max_pairwise_product max_pairwise_product_lib)
install(TARGETS max_pairwise_product DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_max_pairwise_product "${PROJECT_SOURCE_DIR}/src/max_pairwise_product/test_max_pairwise_product.cpp")
    add_test(test_max_pairwise_product test_max_pairwise_product)
    target_link_libraries(
        test_max_pairwise_product 
        max_pairwise_product_lib
        order_calculations)
endif()
