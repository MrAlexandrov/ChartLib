cmake_minimum_required(VERSION 3.14)
project(ChartLib VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(CHARTLIB_SOURCES
    src/chart.cpp
    src/drawer.cpp
    src/plotter.cpp
    src/utils.cpp
)

set(CHARTLIB_HEADERS
    include/chart.hpp
    include/drawer.hpp
    include/plotter.hpp
    include/types.hpp
    include/utils.hpp
    include/chartlib.hpp
)

# Build library
add_library(chartlib STATIC ${CHARTLIB_SOURCES})
target_include_directories(chartlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Examples (optional)
option(BUILD_EXAMPLES "Build example programs" ON)
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Tests (optional)
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
