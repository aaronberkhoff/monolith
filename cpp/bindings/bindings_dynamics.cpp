#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>  // allows Eigen::Vector3d to convert to numpy arrays
#include "monolith/dynamics.hpp"

namespace py = pybind11;

PYBIND11_MODULE(dynamics, m) {
    m.doc() = "Pybind11 bindings for Dynamic and TwoBody";

    // -------------------- Bind State --------------------
    py::class_<State>(m, "State")
    // init statement
        .def(py::init<const Eigen::Vector3d&,
                    const Eigen::Vector3d&,
                    const Eigen::Vector3d&>(),
            py::arg("position") = Eigen::Vector3d::Zero(),
            py::arg("velocity") = Eigen::Vector3d::Zero(),
            py::arg("acceleration") = Eigen::Vector3d::Zero())
        .def_readwrite("position", &State::position)
        .def_readwrite("velocity", &State::velocity)
        .def_readwrite("acceleration", &State::acceleration)
        .def("set_position", &State::set_position)
        .def("set_velocity", &State::set_velocity)
        .def("set_acceleration", &State::set_acceleration)
        .def("get_position", &State::get_position)
        .def("get_velocity", &State::get_velocity)
        .def("get_acceleration", &State::get_acceleration)
        .def("__matmul__", [](const State& a, const State& b) {
            return a >> b;  // calls overloaded operator@
        });

    // -------------------- Bind Dynamic --------------------
    py::class_<Dynamic, std::shared_ptr<Dynamic>>(m, "Dynamic")
        .def("__call__", &Dynamic::operator());

    // -------------------- Bind TwoBody --------------------
    py::class_<TwoBody, Dynamic, std::shared_ptr<TwoBody>>(m, "TwoBody")
        .def(py::init<double>(),py::arg("mu"))  // constructor with mu
        .def("__call__", &TwoBody::operator())
        .def_readwrite("mu", &TwoBody::mu);
}
