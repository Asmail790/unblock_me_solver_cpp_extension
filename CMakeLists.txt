cmake_minimum_required(VERSION 3.26)

project(
    UnblockMeSolverCppExtension 
    VERSION 1.0
    DESCRIPTION "Extension for UnblockMeSolver in cpp"
    LANGUAGES CXX
    )
    
set(CMAKE_CXX_STANDARD 17) # or 11 ?
set(CMAKE_CXX_STANDARD_REQUIRED True)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)

FetchContent_MakeAvailable(Catch2)

enable_testing()

add_library(Main STATIC 
    "${PROJECT_SOURCE_DIR}/src/main/entry.cpp"
    "${PROJECT_SOURCE_DIR}/src/main/block.cpp"
    "${PROJECT_SOURCE_DIR}/src/main/grid.cpp"
    "${PROJECT_SOURCE_DIR}/src/main/graph.cpp"
)
    
target_include_directories(Main PUBLIC 
    "${PROJECT_SOURCE_DIR}/src/includes/"
)
    
add_executable(MainTests 
    "${PROJECT_SOURCE_DIR}/src/tests/entry.cpp" 
    "${PROJECT_SOURCE_DIR}/src/tests/grid.cpp"
    "${PROJECT_SOURCE_DIR}/src/tests/block.cpp"
    "${PROJECT_SOURCE_DIR}/src/tests/graph.cpp"
    "${PROJECT_SOURCE_DIR}/src/tests/benchmark.cpp"
) 

target_include_directories(MainTests PUBLIC 
    "${PROJECT_SOURCE_DIR}/src/includes/"
)






target_link_libraries(MainTests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(MainTests PUBLIC Main)

add_test(NAME MainTests_ COMMAND MainTests)
