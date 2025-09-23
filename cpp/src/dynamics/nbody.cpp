#include <Eigen/Dense>
#include "monolith/dynamics/nbody.hpp"
#include "monolith/dynamics/state.hpp"

namespace monolith {

    Eigen::Vector3d NBody::single_body(const State& state, const CelestialBody& body) const {

        State n_body_state = body.get_state(state.time, central_body);

        Eigen::Vector3d agent_to_third_body = n_body_state.position - state.position;

        Eigen::Vector3d acceleration = body.mu * (agent_to_third_body / std::pow(agent_to_third_body.norm(), 3) - n_body_state.position / std::pow(n_body_state.position.norm(),3));

        return acceleration;


    };

    State NBody::operator()(const State& state) const {
        State new_state = state;
        Eigen::Vector3d acceleration = Eigen::Vector3d::Zero();

        for (size_t i = 0; i < bodies.size(); ++i) {
            acceleration += single_body(state, bodies[i]);
        }

        new_state.acceleration += acceleration;

        return new_state;
    };



}
