import numpy as np

from typing import Sequence

from monolith.dynamics import State
from monolith.celestial_bodies import CelestialBody

class DynamicsOracle:

    def __init__(self,state: State, planet: CelestialBody, bodies: Sequence[CelestialBody]):

        self.state = state
        self.planet = planet
        self.bodies = bodies

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

    def get_j4_acceleration(self):

        rx = self.state.position[0]
        ry = self.state.position[1]
        rz = self.state.position[2]


        # Compute common terms
        r2 = rx**2 + ry**2 + rz**2  # Square of the radial distance
        r = np.sqrt(r2)  # Radial distance

        R = self.planet.radius # Earth's radius cubed

        # Central body's parameters
        J4 = self.planet.j4  # J3 coefficient
        mu = self.planet.mu  # Gravitational parameter


        ax = 15 * J4 * mu * R**4 * rx / ( 8*r**7) * ( 1 - 14*rz**2 / r**2 + 21*rz**4 / r**4)
        ay = 15 * J4 * mu * R**4 * ry / ( 8*r**7) * ( 1 - 14*rz**2 / r**2 + 21*rz**4 / r**4)
        az = 15 * J4 * mu * R**4 * rz / ( 8*r**7) * ( 5 - 70*rz**2 / (3*r**2) + 21*rz**4 / r**4)

        return np.array([ax,ay,az])

    def get_j5_acceleration(self):

        rx = self.state.position[0]
        ry = self.state.position[1]
        rz = self.state.position[2]


        # Compute common terms
        r2 = rx**2 + ry**2 + rz**2  # Square of the radial distance
        r = np.sqrt(r2)  # Radial distance

        R = self.planet.radius # Earth's radius cubed

        # Central body's parameters
        J5 = self.planet.j5  # J3 coefficient
        mu = self.planet.mu  # Gravitational parameter


        ax = 3 * J5 * mu * R**5 * rx / ( 8*r**9) * ( 35 - 210*rz**2 / r**2 + 231*rz**4 / r**4)
        ay = 3 * J5 * mu * R**5 * ry / ( 8*r**9) * ( 35 - 210*rz**2 / r**2 + 231*rz**4 / r**4)
        az = 3 * J5 * mu * R**5 * rz / ( 8*r**9) * ( 105 - 315*rz**2 / (r**2) + 231*rz**4 / r**4) - 15*J5*mu*R**5 / (8*r**7)

        return np.array([ax,ay,az])

    def get_j6_acceleration(self):

        rx = self.state.position[0]
        ry = self.state.position[1]
        rz = self.state.position[2]


        # Compute common terms
        r2 = rx**2 + ry**2 + rz**2  # Square of the radial distance
        r = np.sqrt(r2)  # Radial distance

        R = self.planet.radius # Earth's radius cubed

        # Central body's parameters
        J6 = self.planet.j6  # J3 coefficient
        mu = self.planet.mu  # Gravitational parameter


        ax = -J6 * mu *R**6 *rx / (16*r**9) * (35 - 945 * rz**2 / r**2 + 3465 * rz**4 / r**4 - 3003 * rz**6 / r**6)
        ay = -J6 * mu *R**6 *ry / (16*r**9) * (35 - 945 * rz**2 / r**2 + 3465 * rz**4 / r**4 - 3003 * rz**6 / r**6)
        az = -J6 * mu *R**6 *rz / (16*r**9) * (245 - 2205 * rz**2 / r**2 + 4851 * rz**4 / r**4 - 3003 * rz**6 / r**6)

        return np.array([ax,ay,az])

    def get_nbody_acceleration(self):

        def single_body(body: CelestialBody):

            mu = body.mu

            # Get ephemeris time
            # current_time = state.time
            # et = spice.str2et(current_time.strftime('%Y-%m-%dT%H:%M:%S'))

            # Get the position and velocity of the third body relative to inertial body
            third_body_state: State
            third_body_state = body.get_state(self.state.time, self.planet)

            # Extract the position (first 3 elements of the self.state vector)
            inertial_to_third_body = (
                third_body_state.position
            )  # 3rd body position in km (X, Y, Z)

            # Agent position relative to inertial body
            inertial_to_agent = self.state.position  # Agent position in km (X, Y, Z)

            # Agent position relative to third body
            agent_to_third_body = inertial_to_third_body - inertial_to_agent

            # Third body acceleration
            accel_third_body = mu * (
                agent_to_third_body / (np.linalg.norm(agent_to_third_body) ** 3)
                - inertial_to_third_body / (np.linalg.norm(inertial_to_third_body) ** 3)
            )

            return accel_third_body

        accel = np.zeros(3)

        for body in self.bodies:
            accel += single_body(body)

        return accel
