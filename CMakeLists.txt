cmake_minimum_required(VERSION 3.10)
project(BigInteger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall")

find_package(Threads REQUIRED)

#-----------------
# Main user program
#-----------------
file(GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/Exceptions.h
        ${PROJECT_SOURCE_DIR}/BigInteger.*)

add_executable(BigInteger ${SRC_FILES})

#-------------------
# Test
#-------------------
enable_testing()
include_directories(${COMMON_INCLUDES})

file(GLOB TEST_SRC_FILES
        ${PROJECT_SOURCE_DIR}/test/src/*.cpp
        ${PROJECT_SOURCE_DIR}/Exceptions.h
        ${PROJECT_SOURCE_DIR}/BigInteger.*)

add_executable(runAllTests ${TEST_SRC_FILES})
target_link_libraries(runAllTests gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
