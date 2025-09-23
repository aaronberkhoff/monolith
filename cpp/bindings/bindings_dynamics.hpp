#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>  // allows Eigen::Vector3d to convert to numpy arrays
#include <pybind11/stl.h>

#include "monolith/dynamics/dynamics.hpp"
#include "monolith/dynamics/state.hpp"
#include "monolith/dynamics/two_body.hpp"
#include "monolith/dynamics/j2.hpp"
#include "monolith/dynamics/j3.hpp"
#include "monolith/dynamics/j4.hpp"
#include "monolith/dynamics/j5.hpp"
#include "monolith/dynamics/j6.hpp"
#include "monolith/dynamics/nbody.hpp"

#include "monolith/celestial_bodies/celestial_bodies.hpp"

#include "monolith/time/time.hpp"

using namespace monolith;

namespace py = pybind11;

inline void bind_dynamics(py::module_ &m) {
    m.doc() = "Pybind11 bindings for Dynamic and TwoBody";

    // -------------------- Bind State --------------------
    py::class_<State>(m, "State")
        .def(py::init<const Eigen::Vector3d&,
                      const Eigen::Vector3d&,
                      const Eigen::Vector3d&,
                      const TimeParameter&>(),
             py::arg("position") = Eigen::Vector3d::Zero(),
             py::arg("velocity") = Eigen::Vector3d::Zero(),
             py::arg("acceleration") = Eigen::Vector3d::Zero(),
             py::arg("time") = 0.0)
        .def_readwrite("position", &State::position)
        .def_readwrite("velocity", &State::velocity)
        .def_readwrite("acceleration", &State::acceleration)
        .def_readwrite("time", &State::time)
        .def("__matmul__", [](const State& a, const State& b) { return a >> b; });

    // -------------------- Bind OE --------------------
    py::class_<OrbitalElements>(m, "OrbitalElements")
        .def(py::init<const double,
                      const double,
                      const double,
                      const double,
                      const double,
                      const double>(),
             py::arg("sma")  = 7000.0,
             py::arg("ecc")  = 0.0,
             py::arg("inc")  = 0.0,
             py::arg("raan") = 0.0,
             py::arg("arg")  = 0.0,
             py::arg("nu")   = 0.0)

        .def_readwrite("sma",  &OrbitalElements::sma)
        .def_readwrite("ecc",  &OrbitalElements::ecc)
        .def_readwrite("inc",  &OrbitalElements::inc)
        .def_readwrite("raan", &OrbitalElements::raan)
        .def_readwrite("arg",  &OrbitalElements::arg)
        .def_readwrite("nu",   &OrbitalElements::nu)

        .def("get_state", &OrbitalElements::get_state, py::arg("mu"));

    // -------------------- Bind Dynamic --------------------
    py::class_<Dynamic, std::shared_ptr<Dynamic>>(m, "Dynamic")
        .def("__call__", &Dynamic::operator(), py::arg("state"));

    // -------------------- Bind TwoBody --------------------
    py::class_<TwoBody, Dynamic, std::shared_ptr<TwoBody>>(m, "TwoBody")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &TwoBody::operator(), py::arg("state"))
        .def_readwrite("central_body", &TwoBody::central_body);

    // -------------------- Bind J2 --------------------
    py::class_<J2, Dynamic, std::shared_ptr<J2>>(m, "J2")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &J2::operator(), py::arg("state"))
        .def_readwrite("central_body", &J2::central_body);

    // -------------------- Bind J3 --------------------
    py::class_<J3, Dynamic, std::shared_ptr<J3>>(m, "J3")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &J3::operator(), py::arg("state"))
        .def_readwrite("central_body", &J3::central_body);

    // -------------------- Bind J4 --------------------
    py::class_<J4, Dynamic, std::shared_ptr<J4>>(m, "J4")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &J4::operator(), py::arg("state"))
        .def_readwrite("central_body", &J4::central_body);
    // -------------------- Bind J5 --------------------
    py::class_<J5, Dynamic, std::shared_ptr<J5>>(m, "J5")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &J5::operator(), py::arg("state"))
        .def_readwrite("central_body", &J5::central_body);
    // -------------------- Bind J6 --------------------
    py::class_<J6, Dynamic, std::shared_ptr<J6>>(m, "J6")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &J6::operator(), py::arg("state"))
        .def_readwrite("central_body", &J6::central_body);

    // -------------------- Bind Nbody --------------------
    py::class_<NBody, Dynamic, std::shared_ptr<NBody>>(m, "NBody")
        .def(py::init<const std::vector<CelestialBody>&, const CelestialBody&>(),
             py::arg("bodies"),
             py::arg("central_body"))
        .def("__call__", &NBody::operator(), py::arg("state"));
}
