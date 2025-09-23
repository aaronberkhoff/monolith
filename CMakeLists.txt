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

# ---------------- CSPICE ----------------
set(CSPICE_ROOT "${CMAKE_SOURCE_DIR}/third_party/cspice")
set(CSPICE_LIBS
    ${CSPICE_ROOT}/lib/cspice.a
    ${CSPICE_ROOT}/lib/csupport.a
)
include_directories(${CSPICE_ROOT}/include)

# ---------------- Core C++ Library ----------------
file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/cpp/src/*.cpp
)

add_library(monolith SHARED ${CORE_SOURCES})
target_include_directories(monolith PUBLIC
    ${CMAKE_SOURCE_DIR}/cpp/include
    ${CSPICE_ROOT}/include
)
target_link_libraries(monolith PUBLIC Eigen3::Eigen ${CSPICE_LIBS})

set(PY_FOLDER ${CMAKE_SOURCE_DIR}/python/monolith)
set(MODULE_TARGETS "")

# Loop over subdirectories in cpp/src/
file(GLOB children RELATIVE ${CMAKE_SOURCE_DIR}/cpp/src ${CMAKE_SOURCE_DIR}/cpp/src/*)

foreach(child ${children})
    if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/src/${child})

        # Skip if it’s a bindings folder
        if(IS_DIRECTORY ${CMAKE_SOURCE_DIR}/cpp/bindings/${child})
            message(STATUS "Skipping binding directory: ${child}")
            continue()
        endif()

        # Only include the binding file for the module; implementation code will be compiled into the .so
        set(BINDING_FILE ${CMAKE_SOURCE_DIR}/cpp/bindings/bindings_${child}.cpp)
        if(EXISTS ${BINDING_FILE})
            pybind11_add_module(${child} ${BINDING_FILE})

            target_include_directories(${child} PRIVATE
                ${CMAKE_SOURCE_DIR}/cpp/include
                ${CSPICE_ROOT}/include
            )

            target_link_libraries(${child} PRIVATE Eigen3::Eigen ${CSPICE_LIBS} monolith)


            set_target_properties(${child} PROPERTIES
                OUTPUT_NAME "${child}"
                LIBRARY_OUTPUT_DIRECTORY ${PY_FOLDER}
            )

            list(APPEND MODULE_TARGETS ${child})
            message(STATUS " -> Added Python module: ${child}")
        else()
            message(WARNING "No binding file found for module '${child}' (expected: bindings_${child}.cpp)")
        endif()
    endif()
endforeach()


# ---------------- Install ----------------
install(DIRECTORY ${CMAKE_SOURCE_DIR}/python/monolith
        DESTINATION .
        FILES_MATCHING PATTERN "*.py")

install(TARGETS ${MODULE_TARGETS}
        LIBRARY DESTINATION monolith)
