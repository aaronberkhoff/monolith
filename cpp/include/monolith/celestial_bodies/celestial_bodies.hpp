#pragma once
#include <string>
#include "monolith/time/time.hpp"
#include "monolith/dynamics/state.hpp"

namespace monolith {
    constexpr const char* DEFAULT_INERTIAL_FRAME = "J2000";
    class CelestialBody {
    public:
        std::string name;
        double mu;
        double radius;
        double j2;
        double j3;
        double j4;
        double j5;
        double j6;
        int spice_id;

        CelestialBody() = default;

        CelestialBody(const std::string& name_,
            double mu_,
            double radius_,
            double j2_,
            double j3_,
            double j4_,
            double j5_,
            double j6_,
            int spice_id_)
            : name(name_), mu(mu_), radius(radius_),
            j2(j2_), j3(j3_),j4(j4_),j5(j5_),j6(j6_),
            spice_id(spice_id_) {}

        virtual ~CelestialBody() = default;

        State get_state(const TimeParameter& time, const CelestialBody& central_body) const;
    };

    // ---------------- Earth ----------------
    class Earth : public CelestialBody {
    public:
        Earth()
            : CelestialBody("Earth",
                    3.986004415e5,     // km^3/s^2 (μ)
                    6.3781363e3,       // km (radius)
                    1.0826266835531513e-3,  // J2
                    -2.53265648533224e-6,    // J3
                    -1.619621591367e-6,      // J4
                    -2.2729608286870e-7,     // J5
                    5.4068123910708e-7,     // J6
                    399) {}
    };


    // ---------------- Moon ----------------
    class Moon : public CelestialBody {
    public:
        Moon()
            : CelestialBody("Moon",
                    4902.800066,  // km^3/s^2
                    1737.4,       // km
                    0.0002027,    // j2
                    0.0,          // j3
                    0.0,          // j4
                    0.0,          // j5
                    0.0,          // j6
                    301) {}       // spice_id
    };
} // namespace monolith
