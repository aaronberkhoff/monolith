#include <Eigen/Dense>
#include "monolith/dynamics/j3.hpp"
#include "monolith/dynamics/state.hpp"

namespace monolith {

    State J3::operator()(const State& state) const {
    State new_state = state;  // copy input

    // Extract position
    double rx = state.position[0];
    double ry = state.position[1];
    double rz = state.position[2];

    // Common terms
    double r2 = rx * rx + ry * ry + rz * rz;
    double r = std::sqrt(r2);
    double r7 = std::pow(r, 7);

    double R3 = std::pow(central_body.radius, 3);  // Earth's radius cubed
    double J3 = central_body.j3;
    double mu = central_body.mu;

    double alpha = -5.0 * J3 * mu * R3 / (2.0 * r7);
    double beta  = 3.0 * rz - 7.0 * rz * rz * rz / r2;
    double gamma = 6.0 * rz * rz - 7.0 * std::pow(rz, 4) / r2 - 0.6 * r2; // (3/5 = 0.6)

    // Accelerations
    double ax = alpha * rx * beta;
    double ay = alpha * ry * beta;
    double az = alpha * gamma;

    new_state.acceleration = Eigen::Vector3d(ax, ay, az);
    return new_state;
};

}
