cmake_minimum_required(VERSION 3.26)

project(UnblockMeSolverCppExtension VERSION 1.0)
enable_testing()
set(CMAKE_CXX_STANDARD 11) # or 17 ?
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory("${PROJECT_SOURCE_DIR}/libs/catch2")



add_executable(Main "${PROJECT_SOURCE_DIR}/src/main/main.cpp")
add_executable(MainTests "${PROJECT_SOURCE_DIR}/src/tests/main.cpp" "${PROJECT_SOURCE_DIR}/src/tests/utils.cpp") 

target_link_libraries(MainTests PRIVATE Catch2::Catch2WithMain)

add_test(NAME MainTests_ COMMAND MainTests)