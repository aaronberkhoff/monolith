#include <Eigen/Dense>
#include "monolith/dynamics/j5.hpp"
#include "monolith/dynamics/state.hpp"

namespace monolith {

    State J5::operator()(const State& state) const {
    State new_state = state;  // start with a copy

    // compute common terms
    double r = state.position.norm();
    double r2     = r * r;
    double r4     = r2 * r2;
    double r5     = r4 * r;
    double r7     = r5 * r2;
    double r9     = r7 * r2;

    double rx     = state.position[0];
    double ry     = state.position[1];
    double rz     = state.position[2];

    double rz2    = rz * rz;
    double rz4    = rz2 * rz2;

    double R5     = std::pow(central_body.radius,5);

    double alpha = 3 * central_body.j5 * central_body.mu * R5 / ( 8*r9);
    double beta  = ( 35 - 210*rz2 / r2 + 231*rz4 / r4);

    //  Compute accelerations using Vallado's formulation -> missing a factor of -1.5?
    double ax = alpha * rx * beta;
    double ay = alpha * ry * beta;
    double az = alpha * rz * ( 105 - 315*rz2 / (r2) + 231*rz4 / r4) - 15*central_body.j5*central_body.mu*R5 / (8*r7);

    new_state.acceleration = Eigen::Vector3d(ax,ay,az);

    return new_state;
};

}
