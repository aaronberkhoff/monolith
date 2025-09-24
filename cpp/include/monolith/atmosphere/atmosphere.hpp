#pragma once
#include "monolith/celestial_bodies/celestial_bodies.hpp"

namespace monolith {

    struct AtmosphereParameters {
        public:
            double density_reference; // rho0
            double altitude_reference; //h0
            double altitude_scale; // H
    };

    class AtmosphereModel {
        public:

            AtmosphereModel() = default;
            virtual ~AtmosphereModel() = default;

            AtmosphereParameters operator() (const State& state) const;

            virtual AtmosphereParameters get_parameters(const State& state) const = 0;



    };

    class EarthModel: public AtmosphereModel {
        public:
            CelestialBody central_body = Earth();
    };

    // US standard atmosphere
    class ExponentialStepEarthModel : public EarthModel {
        public:
            AtmosphereParameters get_parameters(const State& state) const override;
        private:
            static constexpr std::array<AtmosphereParameters, 28> layers = {{
                {3.019e-15, 1000, 268},
                {5.245e-15,  900, 181.05},
                {1.170e-14,  800, 124.64},
                {3.614e-14,  700,  88.667},
                {1.454e-13,  600,  71.835},
                {6.967e-13,  500,  63.822},
                {1.585e-12,  450,  60.828},
                {3.725e-12,  400,  58.515},
                {9.518e-12,  350,  53.298},
                {2.418e-11,  300,  53.628},
                {7.248e-11,  250,  45.546},
                {2.789e-10,  200,  37.105},
                {5.464e-10,  180,  29.740},
                {2.070e-9,   150,  22.523},
                {3.845e-9,   140,  16.149},
                {8.484e-9,   130,  12.636},
                {2.438e-8,   120,   9.473},
                {9.661e-8,   110,   7.263},
                {5.297e-7,   100,   5.877},
                {3.396e-6,    90,   5.382},
                {1.905e-5,    80,   5.799},
                {8.770e-5,    70,   6.549},
                {3.206e-4,    60,   7.714},
                {1.057e-3,    50,   8.382},
                {3.972e-3,    40,   7.554},
                {1.774e-2,    30,   6.682},
                {3.899e-2,    25,   6.349},
                {1.225,        0,   7.249}
            }};


    };
}
