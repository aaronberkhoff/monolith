#pragma once
#include <Eigen/Dense>
#include "monolith/time/time.hpp"
#include "monolith/utils/transforms.hpp"

namespace monolith {

    class State {
        public:
            Eigen::Vector3d position;
            Eigen::Vector3d velocity;
            Eigen::Vector3d acceleration;
            TimeParameter time;

            // Single constructor with defaults
            State(const Eigen::Vector3d& position_     = Eigen::Vector3d::Zero(),
                const Eigen::Vector3d& velocity_     = Eigen::Vector3d::Zero(),
                const Eigen::Vector3d& acceleration_ = Eigen::Vector3d::Zero(),
                const TimeParameter& time_           = TimeParameter())
                : position(position_), velocity(velocity_), acceleration(acceleration_), time(time_) {}

            // Example operator (unusual use of >>)
            State operator>>(const State& other) const {
                Eigen::Vector3d accel = this->acceleration + other.acceleration;
                return State(this->position, this->velocity, accel, this->time);
            }
    };

    class OrbitalElements {

        public:
            double sma;
            double ecc;
            double inc;
            double raan;
            double arg;
            double nu;

        OrbitalElements(const double sma_ = 7000.0, const double ecc_ = 0.0, const double inc_ = 0.0,
                        const double raan_ = 0.0,   const double arg_ = 0.0, const double nu_ = 0.0)
                        : sma(sma_), ecc(ecc_), inc(inc_), raan(raan_), arg(arg_), nu(nu_) {}

        State get_state(double mu) const {
            Eigen::VectorXd rv = oe2rv(sma, ecc, inc, raan, arg, nu, mu);
            Eigen::Vector3d r = rv.head<3>();      // first 3 elements
            Eigen::Vector3d v = rv.tail<3>();      // last 3 elements

            return State(r, v);
        }


    };

} // namespace monolith
