#include <pybind11/pybind11.h>
#include "bindings_dynamics.hpp"

namespace py = pybind11;

PYBIND11_MODULE(dynamics, m) {
    m.doc() = "Dynamics models";
    bind_dynamics(m);
    // Import Planet class from monolith.planets to help stubgen
    py::module_ celestial_bodies = py::module_::import("monolith.celestial_bodies");
    m.attr("CelestialBody") = celestial_bodies.attr("CelestialBody");

}
