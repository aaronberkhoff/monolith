#include <Eigen/Dense>
#include "monolith/dynamics/j4.hpp"
#include "monolith/dynamics/state.hpp"

namespace monolith {

    State J4::operator()(const State& state) const {
    State new_state = state;  // start with a copy

    // compute common terms
    double r = state.position.norm();
    double r2     = r * r;
    double r4     = r2 * r2;
    double r5     = r4 * r;
    double r7     = r5 * r2;
    double R4     = std::pow(central_body.radius,4);
    double rx     = state.position[0];
    double ry     = state.position[1];
    double rz     = state.position[2];

    double rz2    = rz * rz;
    double rz4    = rz2 * rz2;

    double alpha = central_body.mu * R4 / (8*r7);
    double beta  = ( 1 - 14*rz2 / r2 + 21*rz4 / r4);

    //  Compute accelerations using Vallado's formulation -> missing a factor of -1.5?
    double ax = 15 * central_body.j4 * alpha * rx * beta;
    double ay = 15 * central_body.j4 * alpha * ry * beta;
    double az = 15 * central_body.j4 * alpha * rz * ( 5 - 70*rz2 / (3*r2) + 21*rz4 / r4);

    new_state.acceleration = Eigen::Vector3d(ax,ay,az);

    return new_state;
};

}
