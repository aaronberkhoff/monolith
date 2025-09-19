#pragma once
#include <Eigen/Dense>
#include "monolith/dynamics/state.hpp"
namespace monolith {

class Dynamic {
public:
    // Virtual destructor (important for inheritance!)
    virtual ~Dynamic() = default;

    // Abstract function that will do calculations
    virtual State operator()(const State& state) const = 0;

};

} //namespace monolith
