#pragma once
#include <Eigen/Dense>

class State {
public:
    virtual ~State() = default; // Inheritance

    Eigen::Vector3d position;     // position
    Eigen::Vector3d velocity;     // velocity
    Eigen::Vector3d acceleration; // acceleration

    // setters
    void set_position(const Eigen::Vector3d& pos);
    void set_velocity(const Eigen::Vector3d& vel);
    void set_acceleration(const Eigen::Vector3d& acc);

    // getters
    Eigen::Vector3d get_position() const;
    Eigen::Vector3d get_velocity() const;
    Eigen::Vector3d get_acceleration() const;
};


class Dynamic {
public:
    // Virtual destructor (important for inheritance!)
    virtual ~Dynamic() = default;

    // Abstract function that will do calculations
    virtual State func(const State& state) const = 0;

};

class TwoBody : public Dynamic {
public:
    explicit TwoBody(double mu_) : mu(mu_) {} // Initializer
    State func(const State& state) const override; // base function

private:
    double mu;
};
