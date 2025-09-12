"""
Unit tests for the dynamics folders

"""
from monolith.dynamics import State, TwoBody
from monolith.planets import Earth, Moon
import numpy as np

def test_dynamics_initialize():
    """
    Tests the init of the Dynamics class
    """

    state = State(position = np.array([1,1,1]))
    two_body = TwoBody(mu=1)

    new_state = two_body(state)

    newer_state = new_state @ state


def test_planets():

    earth = Earth()
    moon = Moon()

    pass


if __name__ == "__main__":

    test_dynamics_initialize()
    test_planets()
