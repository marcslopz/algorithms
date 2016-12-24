add_library(merge_sort "${PROJECT_SOURCE_DIR}/src/sort/merge_sort.cpp")

#add_executable(
#    max_pairwise_product
#    "${PROJECT_SOURCE_DIR}/src/max_pairwise_product/main.cpp")
#target_link_libraries(max_pairwise_product max_pairwise_product_lib)
#install(TARGETS max_pairwise_product DESTINATION bin)

if(BUILD_TESTING)
    add_executable(test_merge_sort "${PROJECT_SOURCE_DIR}/src/sort/test_merge_sort.cpp")
    add_test(test_merge_sort test_merge_sort)
    target_link_libraries(
        test_merge_sort 
        merge_sort
        order_calculations)
endif()
