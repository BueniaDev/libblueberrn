cmake_minimum_required(VERSION 3.13)
project(libblueberrn)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE OFF)

option(BUILD_SDL2 "Enables the command-line frontend (requires SDL2)." OFF)
option(BUILD_DEBUG "Enables the debug build (includes drivers that boot, but are still far from playable." OFF)
option(BUILD_DEVELOPER "Enables the developer build (includes all functional and WIP drivers, for developers only)." OFF)

set(LIBBLUEBERRN_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libblueberrn/include")

include_directories(AFTER PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libblueberrn")
include_directories(AFTER PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libblueberrn/components")
include_directories(AFTER PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libblueberrn/include/libblueberrn")
include_directories(AFTER PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libblueberrn/include/drivers")

if (BUILD_SDL2 STREQUAL "ON")
	add_subdirectory(blueberrn-SDL)
endif()

if (BUILD_DEBUG)
	add_compile_definitions(BERRN_DEBUG_BUILD)
endif()

if (BUILD_DEVELOPER)
	add_compile_definitions(BERRN_DEVELOPER_BUILD)
endif()

add_subdirectory(libblueberrn)

add_library(blueberrn ${LIBBLUEBERRN} ${LIBBLUEBERRN_HEADERS})
target_include_directories(blueberrn PUBLIC ${LIBBLUEBERRN_INCLUDE_DIR})
target_compile_definitions(blueberrn PRIVATE LIBBLUEBERRN_STATIC=1 _CRT_SECURE_NO_WARNINGS=1)
target_link_libraries(blueberrn PUBLIC components)
add_library(libblueberrn ALIAS blueberrn)

if (WIN32)
    message(STATUS "Operating system is Windows.")
    if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
	target_compile_options(blueberrn PRIVATE -Wall -Wextra)
	message(STATUS "Compiler is MinGW.")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL MSVC)
	message(STATUS "MSVC support is HIGHLY experimental, and may not even compile correctly, so be EXTREMELY careful here!")
	target_compile_options(blueberrn PRIVATE /W4)
	message(STATUS "Compiler is MSVC.")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	target_compile_options(blueberrn PRIVATE -Wall -Wextra)
	message(STATUS "Compiler is Clang.")
    else()
	message(SEND_ERROR "Compiler not supported.")
	return()
    endif()
elseif(UNIX AND NOT APPLE)
    message(STATUS "Operating system is Linux.")
    if (CMAKE_CXX_COMPILER_ID STREQUAL GNU)
	target_compile_options(blueberrn PRIVATE -Wall -Wextra)
	message(STATUS "Compiler is GCC.")
    elseif (CMAKE_CXX_COMPILER_ID STREQUAL Clang)
	target_compile_options(blueberrn PRIVATE -Wall -Wextra)
	message(STATUS "Compiler is Clang.")
    else()
	message(SEND_ERROR "Compiler not supported.")
	return()
    endif()
elseif(APPLE)
    message(STATUS "Operating system is Mac.")
    if (CMAKE_CXX_COMPILER_ID STREQUAL AppleClang)
	target_compile_options(blueberrn PRIVATE -Wall -Wextra)
	message(STATUS "Compiler is AppleClang.")
    else()
	message(SEND_ERROR "Compiler not supported.")
	return()
    endif()
else()
    message(SEND_ERROR "Operating system not supported.")
    return()
endif()