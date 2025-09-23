#include <pybind11/pybind11.h>
#include "bindings_time.hpp"

namespace py = pybind11;

PYBIND11_MODULE(time, m) {
    m.doc() = "Time module";
    bind_time(m);
    // py::module_ celestial_bodies = py::module_::import("monolith.time");
    // m.attr("TimeParameter") = celestial_bodies.attr("TimeParameter");
}
