#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "monolith/time/time.hpp"

using namespace monolith;

namespace py = pybind11;

inline void bind_time(py::module_ &m) {
    m.doc() = "Pybind11 bindings for Time Module";

    // -------------------- Bind Time --------------------
    py::class_<TimeParameter>(m, "TimeParameter")
        .def(py::init<>())
        .def(py::init<const int ,
                      const int ,
                      const int ,
                      const int ,
                      const int ,
                      const int ,
                      const double
                      >(),
             py::arg("year")   ,
             py::arg("month")  ,
             py::arg("day")    ,
             py::arg("hour")   ,
             py::arg("minute") ,
             py::arg("second") ,
             py::arg("microsecond")
            )
        .def("get_et", &TimeParameter::get_et)
        .def_readwrite("year",        &TimeParameter::year)
        .def_readwrite("month",       &TimeParameter::month)
        .def_readwrite("day",         &TimeParameter::day)
        .def_readwrite("hour",        &TimeParameter::hour)
        .def_readwrite("minute",      &TimeParameter::minute)
        .def_readwrite("second",      &TimeParameter::second)
        .def_readwrite("microsecond", &TimeParameter::microsecond);


    }
