
#include <Eigen/Dense>
#include <string>
#include "monolith/celestial_bodies/celestial_bodies.hpp"
#include "monolith/dynamics/state.hpp"
#include "monolith/time/time.hpp"

extern "C" {
    #include "SpiceUsr.h"
}

namespace monolith {

    State CelestialBody::get_state(const TimeParameter& time, const CelestialBody& central_body) const {
        // Convert UTC to ephemeris time
        SpiceDouble et = time.get_et();

        // Prepare output arrays
        SpiceDouble state[6]; // [x, y, z, vx, vy, vz]
        SpiceDouble lt;

        // Convert IDs to strings safely
        std::string inertial  = std::to_string(central_body.spice_id);
        std::string target = std::to_string(this->spice_id);

        // Call CSPICE function
        spkezr_c(
            target.c_str(),       // Target body
            et,                   // Ephemeris time
            DEFAULT_INERTIAL_FRAME,// Reference frame
            "NONE",               // Aberration correction
            inertial.c_str(),     // Observer body
            state,                // Output state
            &lt                   // Light-time output
        );

        // Construct and return a State object
        Eigen::Vector3d position(state[0], state[1], state[2]);
        Eigen::Vector3d velocity(state[3], state[4], state[5]);
        Eigen::Vector3d acceleration = Eigen::Vector3d::Zero(); // If you compute acceleration elsewhere

        return State(position, velocity, acceleration, time);
    };
}
