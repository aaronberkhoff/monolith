#include <Eigen/Dense>
#include "monolith/dynamics/two_body.hpp"
#include "monolith/dynamics/state.hpp"

namespace monolith {

    State TwoBody::operator()(const State& state) const {
    State new_state = state;  // start with a copy

    double r_norm = state.position.norm();

    new_state.acceleration += -central_body.mu * state.position / (r_norm * r_norm * r_norm);

    return new_state;
};

}
