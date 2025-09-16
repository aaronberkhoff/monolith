#include <pybind11/pybind11.h>
#include "bindings_planets.hpp"

namespace py = pybind11;

PYBIND11_MODULE(planets, m) {
    m.doc() = "Dynamics models";
    bind_planets(m);
}
