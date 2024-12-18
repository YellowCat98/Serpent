cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

project(PythonThingIDK VERSION 1.0.0)

# Set up the mod binary
file(GLOB SOURCES
    src/*.cpp
    src/ui/*.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "Unable to find Geode SDK! Please define GEODE_SDK environment variable to point to Geode")
else()
    message(STATUS "Found Geode: $ENV{GEODE_SDK}")
endif()

# Set the static CPython library and include paths
set(PYTHON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/cpython/include/")  # Replace with the actual include path
set(PYTHON_LIB_PATH "${CMAKE_SOURCE_DIR}/cpython/PCbuild/amd64/python313.lib")  # Replace with the actual static library path

# Add the Python include path
include_directories(${PYTHON_INCLUDE_DIR})

# Add the path to the static Python library
link_directories(${PYTHON_LIB_PATH})

set(FETCHCONTENT_TIMEOUT 100000000)

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Ensure pybind11 is added
CPMAddPackage(
    NAME pybind11
    GITHUB_REPOSITORY pybind/pybind11
    VERSION 2.13.6
)

# Link the static Python library
target_link_libraries(${PROJECT_NAME} pybind11::embed pybind11::module ${PYTHON_LIB_PATH})

# Set up Geode mod
setup_geode_mod(${PROJECT_NAME})
