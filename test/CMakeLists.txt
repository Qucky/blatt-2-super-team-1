cmake_minimum_required(VERSION 2.6)

#set(FILES_TO_TEST ../src/word_table.cpp)
SET(CMAKE_CXX_FLAGS "-std=c++11")
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests Main_TestAll.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)