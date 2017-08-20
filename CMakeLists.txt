cmake_minimum_required(VERSION 3.4.1)
include(cmake/macros.cmake)

project(bloom-filter)

SetBuildSettings()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

GetFiles(GLOB_RECURSE SRC_FILES bloom-filter/*)
GetFiles(GLOB_RECURSE SRC_FILES third-parties/xxhash/src/*)

add_library(bloom-filter STATIC ${SRC_FILES})

include_directories(
	bloom-filter
	third-parties/xxhash/src/
)