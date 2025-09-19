#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>  // allows Eigen::Vector3d to convert to numpy arrays

#include "monolith/dynamics/dynamics.hpp"
#include "monolith/dynamics/two_body.hpp"
#include "monolith/dynamics/j2.hpp"
#include "monolith/dynamics/j3.hpp"
#include "monolith/dynamics/j4.hpp"
#include "monolith/dynamics/j5.hpp"
#include "monolith/dynamics/j6.hpp"

#include "monolith/celestial_bodies/celestial_bodies.hpp"

using namespace monolith;

namespace py = pybind11;

inline void bind_dynamics(py::module_ &m) {
    m.doc() = "Pybind11 bindings for Dynamic and TwoBody";

    // -------------------- Bind State --------------------
    py::class_<State>(m, "State")
        .def(py::init<const Eigen::Vector3d&,
                      const Eigen::Vector3d&,
                      const Eigen::Vector3d&>(),
             py::arg("position") = Eigen::Vector3d::Zero(),
             py::arg("velocity") = Eigen::Vector3d::Zero(),
             py::arg("acceleration") = Eigen::Vector3d::Zero())
        .def_readwrite("position", &State::position)
        .def_readwrite("velocity", &State::velocity)
        .def_readwrite("acceleration", &State::acceleration)
        .def("__matmul__", [](const State& a, const State& b) { return a >> b; });

    // -------------------- Bind Dynamic --------------------
    py::class_<Dynamic, std::shared_ptr<Dynamic>>(m, "Dynamic")
        .def("__call__", &Dynamic::operator());

    // -------------------- Bind TwoBody --------------------
    py::class_<TwoBody, Dynamic, std::shared_ptr<TwoBody>>(m, "TwoBody")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &TwoBody::operator())
        .def_readwrite("central_body", &TwoBody::central_body);

    // -------------------- Bind J2 --------------------
    py::class_<J2, Dynamic, std::shared_ptr<J2>>(m, "J2")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &J2::operator())
        .def_readwrite("central_body", &J2::central_body);

    // -------------------- Bind J3 --------------------
    py::class_<J3, Dynamic, std::shared_ptr<J3>>(m, "J3")
        .def(py::init<const CelestialBody&>(), py::arg("central_body"))
        .def("__call__", &J3::operator())
        .def_readwrite("central_body", &J3::central_body);
}
