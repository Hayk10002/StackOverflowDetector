cmake_minimum_required(VERSION 3.10)

project(StackOverflowDetector)

set(CMAKE_CXX_STANDARD 23)
add_executable(main main.cpp)

# Add the main executable as a test
enable_testing()
add_test(NAME MainTest COMMAND $<TARGET_FILE:main>)
