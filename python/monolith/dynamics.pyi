"""
Pybind11 bindings for Dynamic and TwoBody
"""
from __future__ import annotations
from monolith.celestial_bodies import CelestialBody
import numpy
__all__: list[str] = ['CelestialBody', 'Dynamic', 'J2', 'J3', 'J4', 'J5', 'J6', 'State', 'TwoBody']
class Dynamic:
    def __call__(self, state: State) -> State:
        ...
class J2(Dynamic):
    central_body: CelestialBody
    def __call__(self, state: State) -> State:
        ...
    def __init__(self, central_body: CelestialBody) -> None:
        ...
class J3(Dynamic):
    central_body: CelestialBody
    def __call__(self, state: State) -> State:
        ...
    def __init__(self, central_body: CelestialBody) -> None:
        ...
class J4(Dynamic):
    central_body: CelestialBody
    def __call__(self, state: State) -> State:
        ...
    def __init__(self, central_body: CelestialBody) -> None:
        ...
class J5(Dynamic):
    central_body: CelestialBody
    def __call__(self, state: State) -> State:
        ...
    def __init__(self, central_body: CelestialBody) -> None:
        ...
class J6(Dynamic):
    central_body: CelestialBody
    def __call__(self, state: State) -> State:
        ...
    def __init__(self, central_body: CelestialBody) -> None:
        ...
class State:
    acceleration: numpy.ndarray[numpy.float64[3, 1]]
    position: numpy.ndarray[numpy.float64[3, 1]]
    velocity: numpy.ndarray[numpy.float64[3, 1]]
    def __init__(self, position: numpy.ndarray[numpy.float64[3, 1]] = ..., velocity: numpy.ndarray[numpy.float64[3, 1]] = ..., acceleration: numpy.ndarray[numpy.float64[3, 1]] = ...) -> None:
        ...
    def __matmul__(self, arg0: State) -> State:
        ...
class TwoBody(Dynamic):
    central_body: CelestialBody
    def __call__(self, state: State) -> State:
        ...
    def __init__(self, central_body: CelestialBody) -> None:
        ...
