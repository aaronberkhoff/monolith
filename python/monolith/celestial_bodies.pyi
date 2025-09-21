"""
Bindings for planetary constants
"""
from __future__ import annotations
import typing
__all__: list[str] = ['CelestialBody', 'Earth', 'Moon']
class CelestialBody:
    j2: float
    j3: float
    j4: float
    j5: float
    j6: float
    mu: float
    name: str
    radius: float
    spice_id: int
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
    def __init__(self, name: str, mu: float, radius: float, j2: float, j3: float, j4: float, j5: float, j6: float, spice_id: int) -> None:
        ...
class Earth(CelestialBody):
    def __init__(self) -> None:
        ...
class Moon(CelestialBody):
    def __init__(self) -> None:
        ...
