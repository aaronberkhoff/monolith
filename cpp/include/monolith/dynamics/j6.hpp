#pragma once
#include "monolith/celestial_bodies/celestial_bodies.hpp"
#include "monolith/dynamics/dynamics.hpp"
#include "monolith/dynamics/state.hpp"

// TODO: consider making CelestialBody a shared pointer
namespace monolith {
class J6 : public Dynamic {
public:

    explicit J6(const CelestialBody& central_body) : central_body(central_body) {}

    State operator()(const State& state) const override; // base function

    CelestialBody central_body;
};
} // namespace monolith
