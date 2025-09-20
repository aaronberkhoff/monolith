#include <Eigen/Dense>
#include "monolith/dynamics/j6.hpp"
#include "monolith/dynamics/state.hpp"

namespace monolith {

    State J6::operator()(const State& state) const {
    State new_state = state;  // start with a copy

    // compute common terms
    double r = state.position.norm();
    double r2     = r * r;
    double r4     = r2 * r2;
    double r6     = r4 * r2;
    double r9     = r6 * r2 * r;

    double rx     = state.position[0];
    double ry     = state.position[1];
    double rz     = state.position[2];

    double rz2    = rz * rz;
    double rz4    = rz2 * rz2;
    double rz6    = rz4 * rz2;

    double R6     = std::pow(central_body.radius,6);

    double alpha  = -central_body.j6 * central_body.mu *R6 / (16*r9);
    double beta   = (35 - 945 * rz2 / r2 + 3465 * rz4 / r4 - 3003 * rz6 / r6) ;

    //  Compute accelerations using Vallado's formulation -> missing a factor of -1.5?
    double ax = alpha * rx * beta;
    double ay = alpha * ry * beta;
    double az = alpha * rz * (245 - 2205 * rz2 / r2 + 4851 * rz4 / r4 - 3003 * rz6 / r6);

    new_state.acceleration = Eigen::Vector3d(ax,ay,az);

    return new_state;
};

}
