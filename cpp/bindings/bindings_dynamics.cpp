#include <pybind11/pybind11.h>
#include "bindings_dynamics.hpp"

namespace py = pybind11;

PYBIND11_MODULE(dynamics, m) {
    m.doc() = "Dynamics models";
    bind_dynamics(m);


    // Import Planet class from monolith.planets to help stubgen
    py::module_ planets = py::module_::import("monolith.planets");
    m.attr("Planet") = planets.attr("Planet");
}
