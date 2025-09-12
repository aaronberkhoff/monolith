#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "monolith/planets.hpp"

namespace py = pybind11;

PYBIND11_MODULE(planets, m) {
    m.doc() = "Bindings for planetary constants";

    py::class_<Planet>(m, "Planet")
        .def_readonly("name", &Planet::name)
        .def_readonly("mu", &Planet::mu)
        .def_readonly("radius", &Planet::radius)
        .def_readonly("j2", &Planet::j2)
        .def_readonly("j3", &Planet::j3)
        .def_readonly("spice_id", &Planet::spice_id);

    py::class_<Earth, Planet>(m, "Earth")
        .def(py::init<>());

    py::class_<Moon, Planet>(m, "Moon")
        .def(py::init<>());
}
