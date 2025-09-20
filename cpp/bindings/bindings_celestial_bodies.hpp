#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "monolith/celestial_bodies/celestial_bodies.hpp"

namespace py = pybind11;

using namespace monolith;

inline void bind_celestial_bodies(py::module_ &m) {
    m.doc() = "Bindings for planetary constants";

    // Planet base class
    py::class_<CelestialBody>(m, "CelestialBody")
        // default ctor
        .def(py::init<>())

        // parameterized ctor
        .def(py::init<
            const std::string&,
            double,
            double,
            double,
            double,
            double,
            double,
            double,
            int
        >(),
        py::arg("name"),
        py::arg("mu"),
        py::arg("radius"),
        py::arg("j2"),
        py::arg("j3"),
        py::arg("j4"),
        py::arg("j5"),
        py::arg("j6"),
        py::arg("spice_id"))

        // fields
        .def_readwrite("name", &CelestialBody::name)
        .def_readwrite("mu", &CelestialBody::mu)
        .def_readwrite("radius", &CelestialBody::radius)
        .def_readwrite("j2", &CelestialBody::j2)
        .def_readwrite("j3", &CelestialBody::j3)
        .def_readwrite("j4", &CelestialBody::j4)
        .def_readwrite("j5", &CelestialBody::j5)
        .def_readwrite("j6", &CelestialBody::j6)
        .def_readwrite("spice_id", &CelestialBody::spice_id);

    // Derived classes
    py::class_<Earth, CelestialBody>(m, "Earth")
        .def(py::init<>());

    py::class_<Moon, CelestialBody>(m, "Moon")
        .def(py::init<>());
}
