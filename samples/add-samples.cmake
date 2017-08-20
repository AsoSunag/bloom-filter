set(ROOT_PATH ${CMAKE_CURRENT_LIST_DIR}/..)

include(${ROOT_PATH}/cmake/macros.cmake)
SetBuildSettings()

macro(CreateSampleExecutable)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

	GetFiles(GLOB SAMPLE_FILES ${CMAKE_SOURCE_DIR}/*)
	add_executable(${SAMPLE_NAME} ${SAMPLE_FILES})

	include_directories(${ROOT_PATH}/bloom-filter)
	target_link_libraries(${SAMPLE_NAME} ${ROOT_PATH}/bin/libbloom-filter.a)
endmacro()