cmake_minimum_required(VERSION 3.15)
project(monolith LANGUAGES CXX)

# Use modern C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create compile_commands.json for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)

find_package(Eigen3 REQUIRED)
find_package(pybind11 REQUIRED)

pybind11_add_module(dynamics bindings/dynamics_bindings.cpp src/dynamics.cpp)
pybind11_add_module(planets bindings/planets_bindings.cpp src/planets.cpp)

target_include_directories(dynamics PRIVATE ${EIGEN3_INCLUDE_DIR})
target_include_directories(planets PRIVATE ${EIGEN3_INCLUDE_DIR})
