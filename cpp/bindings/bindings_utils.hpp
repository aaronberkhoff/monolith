#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>  // Eigen <-> NumPy
#include <pybind11/stl.h>

#include "monolith/utils/transforms.hpp"

using namespace monolith;
namespace py = pybind11;

inline void bind_transforms(py::module_ &m) {
    // Create submodule "transforms" under the given module
    auto transforms = m.def_submodule("transforms", "Orbital/utility transforms");

    // Bind oe2rv
    transforms.def(
        "oe2rv",
        &oe2rv,
        py::arg("sma"),
        py::arg("ecc"),
        py::arg("inc"),
        py::arg("raan"),
        py::arg("arg"),
        py::arg("nu"),
        py::arg("mu"),
        "Convert orbital elements to an inertial Cartesian state [x, y, z, vx, vy, vz]"
    );
}
