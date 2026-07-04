cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(vecos C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PICOTOOL_FORCE_FETCH_FROM_GIT ON CACHE BOOL "" FORCE)

pico_sdk_init()

add_subdirectory(SIMD)