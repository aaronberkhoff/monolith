#include <Eigen/Dense>

using Eigen::Vector3d;
using Eigen::Matrix3d;
using Eigen::VectorXd;

namespace monolith {
    VectorXd oe2rv(double sma, double ecc, double inc,
                double raan, double arg, double nu, double mu)
    {
        // Semi-latus rectum
        double p = sma * (1.0 - ecc * ecc);

        // Radius in orbital plane
        double r = p / (1.0 + ecc * std::cos(nu));

        // Position and velocity in perifocal frame
        Vector3d r_perifocal(r * std::cos(nu),
                            r * std::sin(nu),
                            0.0);

        Vector3d v_perifocal(-std::sqrt(mu / p) * std::sin(nu),
                            std::sqrt(mu / p) * (ecc + std::cos(nu)),
                            0.0);

        // Perifocal-to-inertial rotation matrix
        Matrix3d transform;
        transform << std::cos(raan) * std::cos(arg) - std::sin(raan) * std::sin(arg) * std::cos(inc),
                    -std::cos(raan) * std::sin(arg) - std::sin(raan) * std::cos(arg) * std::cos(inc),
                    std::sin(raan) * std::sin(inc),
                    std::sin(raan) * std::cos(arg) + std::cos(raan) * std::sin(arg) * std::cos(inc),
                    -std::sin(raan) * std::sin(arg) + std::cos(raan) * std::cos(arg) * std::cos(inc),
                    -std::cos(raan) * std::sin(inc),
                    std::sin(arg) * std::sin(inc),
                    std::cos(arg) * std::sin(inc),
                    std::cos(inc);

        // Rotate to inertial frame
        Vector3d r_eci = transform * r_perifocal;
        Vector3d v_eci = transform * v_perifocal;

        // Return combined 6x1 state vector [r; v]
        VectorXd state(6);
        state << r_eci, v_eci;
        return state;
    };

}
