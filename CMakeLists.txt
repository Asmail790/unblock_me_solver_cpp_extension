cmake_minimum_required(VERSION 3.10)

project(
    UnblockMeSolverCppExtension 
    VERSION 1.0
    DESCRIPTION "Very nice project"
    LANGUAGES CXX
    )
    
set(CMAKE_CXX_STANDARD 17) # or 11 ?
set(CMAKE_CXX_STANDARD_REQUIRED True)

#if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    add_compile_options(-O0)
#    message(STATUS "GNU is used")
#endif()

add_compile_options(-O3)
enable_testing()
add_subdirectory(
    "${PROJECT_SOURCE_DIR}/libs/catch2"
)

add_library(Main STATIC 
    "${PROJECT_SOURCE_DIR}/src/main/entry.cpp"
    "${PROJECT_SOURCE_DIR}/src/main/block.cpp"
    "${PROJECT_SOURCE_DIR}/src/main/grid.cpp"
    "${PROJECT_SOURCE_DIR}/src/main/graph.cpp"
)
    
target_include_directories(Main PUBLIC 
    "${PROJECT_SOURCE_DIR}/src/include/"
)
    
add_executable(MainTests 
    "${PROJECT_SOURCE_DIR}/src/tests/entry.cpp" 
    "${PROJECT_SOURCE_DIR}/src/tests/grid.cpp"
    "${PROJECT_SOURCE_DIR}/src/tests/block.cpp"
    "${PROJECT_SOURCE_DIR}/src/tests/graph.cpp"
    "${PROJECT_SOURCE_DIR}/src/tests/benchmark.cpp"
) 

target_include_directories(MainTests PUBLIC 
    "${PROJECT_SOURCE_DIR}/src/include/"
)

target_link_libraries(MainTests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(MainTests PUBLIC Main)

add_test(NAME MainTests_ COMMAND MainTests)
