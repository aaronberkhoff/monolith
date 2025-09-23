"""
Orbital/utility transforms
"""
from __future__ import annotations
import numpy
__all__: list[str] = ['oe2rv']
def oe2rv(sma: float, ecc: float, inc: float, raan: float, arg: float, nu: float, mu: float) -> numpy.ndarray[numpy.float64[m, 1]]:
    """
    Convert orbital elements to an inertial Cartesian state [x, y, z, vx, vy, vz]
    """
