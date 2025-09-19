#include <pybind11/pybind11.h>
#include "bindings_celestial_bodies.hpp"

namespace py = pybind11;

PYBIND11_MODULE(celestial_bodies, m) {
    m.doc() = "celestial_bodies models";
    bind_celestial_bodies(m);
}
