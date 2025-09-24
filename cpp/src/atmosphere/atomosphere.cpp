
#include "monolith/atmosphere/atmosphere.hpp"
#include "monolith/dynamics/state.hpp"
#include "monolith/celestial_bodies/celestial_bodies.hpp"

namespace monolith {

    AtmosphereParameters AtmosphereModel::operator()(const State& state) const {
        return get_parameters(state);
    };

    AtmosphereParameters ExponentialStepEarthModel::get_parameters(const State& state) const {

      double altitude = state.position.norm() - central_body.radius ;

        for (const auto& layer : layers) {
            if (altitude > layer.altitude_reference) {
                return layer;
            }
        }
        return layers.back(); // fallback to surface

    };




}
