cmake_minimum_required(VERSION 3.12)
project(monolith)

set(CMAKE_CXX_STANDARD 23)

find_package(Eigen3 REQUIRED)
find_package(pybind11 REQUIRED)

pybind11_add_module(dynamics bindings/dynamics_bindings.cpp src/dynamics.cpp)

target_include_directories(dynamics PRIVATE ${EIGEN3_INCLUDE_DIR})
