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

    new_state.acceleration = -mu * state.position / (r_norm * r_norm * r_norm);

    return new_state;
}
