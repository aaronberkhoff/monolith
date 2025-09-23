#pragma once
#include "monolith/celestial_bodies/celestial_bodies.hpp"
#include "monolith/dynamics/dynamics.hpp"
#include <vector>

namespace monolith {

    class NBody : public Dynamic {
    public:
        explicit NBody(std::vector<CelestialBody> bodies_, const CelestialBody& central_body_)
            : bodies(std::move(bodies_)), central_body(central_body_)
        {
            // Furnish the kernels automatically
            for (const auto& kernel : DEFAULT_KERNELS) {
                furnsh_c(kernel.c_str());
            }
        }

        State operator()(const State& state) const override;
        Eigen::Vector3d single_body(const State& state, const CelestialBody& body) const;

    private:
        std::vector<CelestialBody> bodies;  // Store all N bodies
        CelestialBody central_body;
        // Static list of kernel paths owned by the class
        inline static const std::vector<std::string> DEFAULT_KERNELS = {
            "data/kernels/de442s.bsp",
            "data/kernels/naif0012.tls",
            "data/kernels/pck00010.tpc"
        };
    };

} // namespace monolith
