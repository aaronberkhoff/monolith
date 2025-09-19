import numpy as np

from monolith.dynamics import State
from monolith.celestial_bodies import CelestialBody

class DynamicsOracle:

    def __init__(self,state: State, planet: CelestialBody):

        self.state = state
        self.planet = planet

    def get_two_body_acceleration(self):

        r = np.linalg.norm(self.state.position)

        acceleration =  -self.planet.mu * self.state.position / r**3

        return acceleration

    def get_j2_acceleration(self):

        rx = self.state.position[0]
        ry = self.state.position[1]
        rz = self.state.position[2]

        # Compute common terms
        r2 = rx**2 + ry**2 + rz**2  # Square of the radial distance
        r = np.sqrt(r2)  # Radial distance
        r5 = r**5
        R2 = self.planet.radius**2  # Earth's radius squared

        # Central body's parameters
        J2 = self.planet.j2  # J2 coefficient
        mu = self.planet.mu  # Gravitational parameter


        alpha = -3 * J2 * mu * R2
        beta = 1 - 5 * rz**2 / r2
        gamma = 2 * r5

        # Compute accelerations using Vallado's formulation
        ax = alpha * rx / gamma * beta
        ay = alpha * ry / gamma * beta
        az = alpha * rz / gamma * (3 - 5 * rz**2 / r2)

        return np.array([ax,ay,az])

    def get_j3_acceleration(self):

        rx = self.state.position[0]
        ry = self.state.position[1]
        rz = self.state.position[2]


        # Compute common terms
        r2 = rx**2 + ry**2 + rz**2  # Square of the radial distance
        r = np.sqrt(r2)  # Radial distance
        r7 = r**7  # r^7

        R3 = self.planet.radius**3  # Earth's radius cubed

        # Central body's parameters
        J3 = self.planet.j3  # J3 coefficient
        mu = self.planet.mu  # Gravitational parameter

        alpha = -5 * J3 * mu * R3 / (2 * r7)
        beta = 3 * rz - 7 * rz**3 / r2
        gamma = 6 * rz**2 - 7 * rz**4 / r2 - 3 / 5 * r2

        # Compute accelerations using Vallado's formulation
        ax = alpha * rx * beta
        ay = alpha * ry * beta
        az = alpha * gamma

        return np.array([ax,ay,az])
