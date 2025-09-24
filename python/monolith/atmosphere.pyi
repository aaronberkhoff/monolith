"""
Bindings for atmosphere models
"""
from __future__ import annotations
import monolith.celestial_bodies
import monolith.dynamics
__all__: list[str] = ['AtmosphereModel', 'AtmosphereParameters', 'EarthModel', 'ExponentialStepEarthModel']
class AtmosphereModel:
    def __call__(self, state: monolith.dynamics.State) -> AtmosphereParameters:
        ...
    def get_parameters(self, state: monolith.dynamics.State) -> AtmosphereParameters:
        ...
class AtmosphereParameters:
    altitude_reference: float
    altitude_scale: float
    density_reference: float
    def __init__(self, density_reference: float, altitude_reference: float, altitude_scale: float) -> None:
        ...
class EarthModel(AtmosphereModel):
    @property
    def central_body(self) -> monolith.celestial_bodies.CelestialBody:
        ...
class ExponentialStepEarthModel:
    def get_parameters(self, state: monolith.dynamics.State) -> AtmosphereParameters:
        ...
