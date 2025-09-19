#pragma once
#include "monolith/celestial_bodies/celestial_bodies.hpp"
#include "monolith/dynamics/dynamics.hpp"
namespace monolith {
class TwoBody : public Dynamic {
public:
    explicit TwoBody(CelestialBody central_body_) : central_body(central_body_) {} // Initializer
    State operator()(const State& state) const override; // base function
    CelestialBody central_body;
};
}
