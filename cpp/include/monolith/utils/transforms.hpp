#pragma once
#include <Eigen/Dense>

namespace monolith {
    Eigen::VectorXd oe2rv(const double sma, const double ecc, const double inc, const double raan, const double arg, const double nu, const double mu);
}
