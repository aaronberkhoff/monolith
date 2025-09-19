#include <Eigen/Dense>
#include "monolith/dynamics/j2.hpp"
#include "monolith/dynamics/state.hpp"

namespace monolith {

    State J2::operator()(const State& state) const {
    State new_state = state;  // start with a copy

    // compute common terms
    double r = state.position.norm();
    double r2     = r * r;
    double r5     = r2 * r2 * r;

    double alpha = -3 * central_body.j2 * central_body.mu * central_body.radius * central_body.radius;
    double beta = 1 - 5 * state.position[2] * state.position[2] / r2;
    double gamma = 2 * r5;

    //  Compute accelerations using Vallado's formulation -> missing a factor of -1.5?
    double ax = alpha * state.position[0] / gamma * beta;
    double ay = alpha * state.position[1] / gamma * beta;
    double az = alpha * state.position[2] / gamma * (3 - 5 * state.position[2]*state.position[2] / r2);

    new_state.acceleration = Eigen::Vector3d(ax,ay,az);

    return new_state;
};

}
