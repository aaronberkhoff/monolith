cmake_minimum_required(VERSION 3.15)
project(monolith LANGUAGES CXX)

# ---------------- Global Settings ----------------
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(COVERAGE "Enable coverage flags" OFF)

if(COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage -fPIC -Wno-maybe-uninitialized")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -fPIC -Wno-maybe-uninitialized -flto=auto")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -flto=auto")
endif()

# ---------------- Dependencies ----------------
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
set(PYBIND11_FINDPYTHON ON)
execute_process(
    COMMAND "${Python3_EXECUTABLE}" -m pybind11 --cmakedir
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
list(APPEND CMAKE_PREFIX_PATH "${pybind11_DIR}")
find_package(pybind11 CONFIG REQUIRED)

find_package(Eigen3 REQUIRED)

# ---------------- Includes ----------------
include_directories(${CMAKE_SOURCE_DIR}/cpp/include)

# Python package folder
set(PY_FOLDER ${CMAKE_SOURCE_DIR}/python/monolith)

# ---------------- Dynamic Modules ----------------
# List of actual pybind11 targets we build
set(MODULE_TARGETS "")

# Loop through each subdirectory under cpp/src/
file(GLOB children RELATIVE ${CMAKE_SOURCE_DIR}/cpp/src ${CMAKE_SOURCE_DIR}/cpp/src/*)

foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/src/${child})
        message(STATUS "Checking for pybind11 module in: ${child}")

        # Collect all .cpp files in that subdirectory
        file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
            ${CMAKE_SOURCE_DIR}/cpp/src/${child}/*.cpp
        )

        # Add matching binding file if it exists, otherwise warn
        set(BINDING_FILE ${CMAKE_SOURCE_DIR}/cpp/bindings/bindings_${child}.cpp)
        if(EXISTS ${BINDING_FILE})
            list(APPEND MODULE_SOURCES ${BINDING_FILE})
        else()
            message(WARNING "No binding file found for module '${child}' (expected: bindings_${child}.cpp)")
        endif()

        # If directory has sources, make a pybind11 module
        if(MODULE_SOURCES)
            message(STATUS " -> Adding pybind11 module: ${child}")
            pybind11_add_module(${child} ${MODULE_SOURCES})
            target_include_directories(${child} PRIVATE ${CMAKE_SOURCE_DIR}/cpp/include)
            target_link_libraries(${child} PRIVATE Eigen3::Eigen)
            set_target_properties(${child} PROPERTIES
                OUTPUT_NAME "${child}"
                LIBRARY_OUTPUT_DIRECTORY ${PY_FOLDER}
            )

            # Save to the list of real targets
            list(APPEND MODULE_TARGETS ${child})
        endif()
    endif()
endforeach()


# ---------------- Install ----------------
install(DIRECTORY ${CMAKE_SOURCE_DIR}/python/monolith
        DESTINATION .
        FILES_MATCHING PATTERN "*.py")

# Only install the modules that were actually built
install(TARGETS ${MODULE_TARGETS}
        LIBRARY DESTINATION monolith)
