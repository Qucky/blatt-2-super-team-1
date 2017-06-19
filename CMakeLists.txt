CMAKE_MINIMUM_REQUIRED (VERSION 3.0)
PROJECT (WordsHash)

ENABLE_TESTING ()

SET (SOURCES main.cpp words.cpp word_table.cpp mainwindow.cpp block.cpp)

# Warnings als Fehler
IF (UNIX)
	#SET (warnings "-Wall -Werror")
	SET (CXXVERSION "-std=c++11")
	SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings} ${cxxversion} -pthread")
ENDIF ()

SET (CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/bin")
SET (EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin")

#INCLUDE_DIRECTORIES ("${CMAKE_SOURCE_DIR}/include")
INCLUDE_DIRECTORIES ("${CMAKE_SOURCE_DIR}")
INCLUDE_DIRECTORIES ("${PROJECT_SOURCE_DIR}")

#ADD_SUBDIRECTORY (src)
ADD_SUBDIRECTORY (test)

ADD_EXECUTABLE (text_hash ${SOURCES})

ADD_TEST (HashTest testAll)
