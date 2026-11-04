cmake_minimum_required(VERSION 3.14)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(matrix_tests test_matrix.cpp ../src/matrix.cpp)

target_include_directories(matrix_tests PRIVATE ../include)

target_link_libraries(
    matrix_tests
    PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(matrix_tests)
