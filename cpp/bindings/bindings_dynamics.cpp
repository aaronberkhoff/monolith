#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>  // allows Eigen::Vector3d to convert to numpy arrays
#include "monolith/dynamics.hpp"

namespace py = pybind11;

PYBIND11_MODULE(dynamics, m) {
    m.doc() = "Pybind11 bindings for Dynamic and TwoBody";

    // -------------------- Bind State --------------------
    py::class_<State>(m, "State")
        .def(py::init<>())  // default constructor
        .def_readwrite("position", &State::position)
        .def_readwrite("velocity", &State::velocity)
        .def_readwrite("acceleration", &State::acceleration)
        .def("set_position", &State::set_position)
        .def("set_velocity", &State::set_velocity)
        .def("set_acceleration", &State::set_acceleration)
        .def("get_position", &State::get_position)
        .def("get_velocity", &State::get_velocity)
        .def("get_acceleration", &State::get_acceleration);

    // -------------------- Bind Dynamic --------------------
    py::class_<Dynamic, std::shared_ptr<Dynamic>>(m, "Dynamic")
        .def("func", &Dynamic::func);

    // -------------------- Bind TwoBody --------------------
    py::class_<TwoBody, Dynamic, std::shared_ptr<TwoBody>>(m, "TwoBody")
        .def(py::init<double>())  // constructor with mu
        .def("func", &TwoBody::func);
}
