add_executable(
    max_pairwise_product 
    "${PROJECT_SOURCE_DIR}/src/max_pairwise_product/max_pairwise_product.cpp")
#target_link_libraries(my_cmake_project Logger)

# install Logger library
#install(TARGETS Logger DESTINATION lib)
#install(FILES "${PROJECT_SOURCE_DIR}/src/logger/logger.h" DESTINATION include)

# install executable file
install(TARGETS max_pairwise_product DESTINATION bin)
#install(FILES "${PROJECT_BINARY_DIR}/Config.h" DESTINATION include)

