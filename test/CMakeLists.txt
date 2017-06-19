CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (WordsHashTest)

ENABLE_TESTING ()

INCLUDE (ExternalProject)

SET (CMAKE_CXX_FLAGS "-std=c++11 -pthread")

SET_DIRECTORY_PROPERTIES (PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR})

#SET (CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/../bin")
SET (CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}")
#SET (EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/../bin")
SET (EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}")

INCLUDE_DIRECTORIES ("${CMAKE_SOURCE_DIR}/../include")
#INCLUDE_DIRECTORIES ("${PROJECT_SOURCE_DIR}")

EXTERNALPROJECT_ADD (
	gtest
	URL https://github.com/google/googletest/archive/release-1.7.0.zip
	INSTALL_COMMAND ""
	CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release)

EXTERNALPROJECT_GET_PROPERTY (gtest binary_dir)
EXTERNALPROJECT_GET_PROPERTY (gtest source_dir)
SET (gtest_library ${binary_dir}/libgtest.a)
SET (gtest_include_dir "${source_dir}/include")
#INCLUDE_DIRECTORIES (SYSTEM "${gtest_include_dir}")
INCLUDE_DIRECTORIES ("${gtest_include_dir}")

# Die Flags -Wall -Werror sollten bei gtest sollten nicht verwendet werden
# Geht nicht, denn gtest war nicht durch add_executable oder add_library
# erzeugt
# https://cmake.org/cmake/help/v3.0/command/target_compile_options.html
#TARGET_COMPILE_OPTIONS (gtest PRIVATE -w)
#TARGET_COMPILE_OPTIONS (gtest PRIVATE -pthread)

ADD_EXECUTABLE (testAll Main_TestAll.cpp)

ADD_DEPENDENCIES (testAll gtest)

SET (Pthread "-pthread")
TARGET_LINK_LIBRARIES (
	testAll
	${gtest_library}
	${Pthreads})

ADD_TEST (HashTest testAll)
