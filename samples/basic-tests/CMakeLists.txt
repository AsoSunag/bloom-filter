cmake_minimum_required(VERSION 3.4.1)

get_filename_component(SAMPLE_NAME ${CMAKE_SOURCE_DIR} NAME)

include(../add-samples.cmake)
CreateSampleExecutable(${SAMPLE_NAME})