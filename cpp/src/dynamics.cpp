#include <Eigen/Dense>
#include "monolith/dynamics.hpp"

// --------------State Object----------------

// ---------------setters--------------------
void State::set_position(const Eigen::Vector3d& pos){
    position = pos;
}
void State::set_velocity(const Eigen::Vector3d& vel){
    velocity = vel;
}
void State::set_acceleration(const Eigen::Vector3d& acc){
    acceleration = acc;
}

// -----------------getters--------------------------

Eigen::Vector3d State::get_position() const{
    return position;
}
Eigen::Vector3d State::get_velocity() const{
    return velocity;
}
Eigen::Vector3d State::get_acceleration() const{
    return acceleration;
}

// ----------------Two Body-------------------------

State TwoBody::operator()(const State& state) const {
    State new_state = state;  // start with a copy

    double r_norm = state.position.norm();

    new_state.acceleration += -mu * state.position / (r_norm * r_norm * r_norm);

    return new_state;
}

// ----------------J2 -------------------------

State J2::operator()(const State& state) const {
    State new_state = state;  // start with a copy

    // compute common terms
    double r_norm = state.position.norm();
    double r2     = r_norm * r_norm;
    double r5     = r2 * r2 * r_norm;

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

// ----------------J3 -------------------------

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
