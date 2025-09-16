#pragma once
#include <Eigen/Dense>
#include "planets.hpp"

class State {
public:
    Eigen::Vector3d position = Eigen::Vector3d::Zero();
    Eigen::Vector3d velocity = Eigen::Vector3d::Zero();
    Eigen::Vector3d acceleration = Eigen::Vector3d::Zero();

    // virtual ~State() = default;

    // this is how you can do default arguments
    State()
        : position(Eigen::Vector3d::Zero()),
          velocity(Eigen::Vector3d::Zero()),
          acceleration(Eigen::Vector3d::Zero()) {}

    State(const Eigen::Vector3d& pos = Eigen::Vector3d::Zero(),
          const Eigen::Vector3d& vel = Eigen::Vector3d::Zero(),
          const Eigen::Vector3d& acc = Eigen::Vector3d::Zero())
        : position(pos), velocity(vel), acceleration(acc) {}


    // setters
    void set_position(const Eigen::Vector3d& pos);
    void set_velocity(const Eigen::Vector3d& vel);
    void set_acceleration(const Eigen::Vector3d& acc);

    // getters
    Eigen::Vector3d get_position() const;
    Eigen::Vector3d get_velocity() const;
    Eigen::Vector3d get_acceleration() const;

    // Overload @ operator
    State operator>>(const State& other) const {
        Eigen::Vector3d accel = this->acceleration + other.acceleration;

        // Return new State with same position & velocity, but new acceleration
        return State(this->position, this->velocity, accel);
    }
};


class Dynamic {
public:
    // Virtual destructor (important for inheritance!)
    virtual ~Dynamic() = default;

    // Abstract function that will do calculations
    virtual State operator()(const State& state) const = 0;

};

class TwoBody : public Dynamic {
public:
    explicit TwoBody(double mu_) : mu(mu_) {} // Initializer
    State operator()(const State& state) const override; // base function
    double mu;
};

// TODO: consider making planet a shared pointer

class J2 : public Dynamic {
public:

    explicit J2(const Planet& central_body) : central_body(central_body) {}

    State operator()(const State& state) const override; // base function

    Planet central_body;
};

class J3 : public Dynamic {
public:

    explicit J3(const Planet& central_body) : central_body(central_body) {}

    State operator()(const State& state) const override; // base function

    Planet central_body;
};

class J4 : public Dynamic {
public:

    explicit J4(const Planet& central_body) : central_body(central_body) {}

    State operator()(const State& state) const override; // base function

    Planet central_body;
};

class J5 : public Dynamic {
public:

    explicit J5(const Planet& central_body) : central_body(central_body) {}

    State operator()(const State& state) const override; // base function

    Planet central_body;
};

class J6 : public Dynamic {
public:

    explicit J6(const Planet& central_body) : central_body(central_body) {}

    State operator()(const State& state) const override; // base function

    Planet central_body;
};
