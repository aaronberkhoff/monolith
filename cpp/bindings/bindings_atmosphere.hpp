#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "monolith/celestial_bodies/celestial_bodies.hpp"
#include "monolith/atmosphere/atmosphere.hpp"

namespace py = pybind11;
using namespace monolith;

inline void bind_atmosphere(py::module_ &m) {
    m.doc() = "Bindings for atmosphere models";

    // Planet base class
    py::class_<AtmosphereParameters>(m, "AtmosphereParameters")
        // parameterized ctor
        .def(py::init<
            const double,
            const double,
            const double
        >(),
        py::arg("density_reference"),
        py::arg("altitude_reference"),
        py::arg("altitude_scale"))
        // fields
        .def_readwrite("density_reference",  &AtmosphereParameters::density_reference)
        .def_readwrite("altitude_reference", &AtmosphereParameters::altitude_reference)
        .def_readwrite("altitude_scale",     &AtmosphereParameters::altitude_scale);

    py::class_<AtmosphereModel>(m, "AtmosphereModel")
            .def("__call__", &AtmosphereModel::operator(),py::arg("state"))
            .def("get_parameters", &AtmosphereModel::operator(),py::arg("state"));

    py::class_<EarthModel, AtmosphereModel>(m, "EarthModel")
            .def_readonly("central_body", &EarthModel::central_body);

    py::class_<ExponentialStepEarthModel>(m, "ExponentialStepEarthModel")
            .def("get_parameters",&ExponentialStepEarthModel::get_parameters, py::arg("state"));
            // .def_read("layers", &ExponentialStepEarthModel::layers);
}
