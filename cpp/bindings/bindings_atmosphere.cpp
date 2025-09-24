#include <pybind11/pybind11.h>
#include "bindings_atmosphere.hpp"

namespace py = pybind11;

PYBIND11_MODULE(atmosphere, m) {
    m.doc() = "atmosphere models";
    bind_atmosphere(m);
    // py::module_ celestial_bodies = py::module_::import("monolith.celestial_bodies");
    // m.attr("CelestialBody") = celestial_bodies.attr("CelestialBody");
}
