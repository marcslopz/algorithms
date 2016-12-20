add_executable(
    integer_multiplication 
    "${PROJECT_SOURCE_DIR}/src/integer_multiplication/main.cpp")
#target_link_libraries(my_cmake_project Logger)

# install Logger library
#install(TARGETS Logger DESTINATION lib)
#install(FILES "${PROJECT_SOURCE_DIR}/src/logger/logger.h" DESTINATION include)

# install executable file
install(TARGETS integer_multiplication DESTINATION bin)
#install(FILES "${PROJECT_BINARY_DIR}/Config.h" DESTINATION include)

