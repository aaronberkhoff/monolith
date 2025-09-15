"""
Unit tests for the dynamics folders

"""
import numpy as np
import pytest


from monolith.dynamics import State, TwoBody
from monolith.planets import Earth, Moon

@pytest.fixture
def default_state():
    """Fixture that creates a default State object at position (1,1,1)."""
    return State(position=np.array([1, 1, 1]))

@pytest.fixture
def default_two_body():
    """Fixture that creates a default TwoBody object with mu = 1.0 ."""
    return TwoBody(mu=1)


def test_state_initialize(default_state:State):
    """
    Tests the init of the State class
    """
    #test default values
    assert np.allclose(default_state.position,np.array([1,1,1]))
    assert np.allclose(default_state.velocity, np.array([0,0,0]))
    assert np.allclose(default_state.acceleration, np.array([0,0,0]))



def test_dynamic_initialize(default_two_body: TwoBody):

    """
    Test the init of the Dynamics class
    """
    assert np.isclose(default_two_body.mu, 1.0, rtol=1e-09, atol=1e-09)

def test_two_body_math(default_state: State, default_two_body: TwoBody):

    #state operation
    new_state = default_two_body(default_state)

    #expected behavior for two body
    position = np.array([1,1,1])
    r_norm = np.linalg.norm(position)
    mu = 1

    acceleration = -mu * position / (r_norm**3)
    expected_state = State(position=np.array([1,1,1]), velocity=np.array([0,0,0]), acceleration=acceleration)

    assert np.allclose(expected_state.position,new_state.position)
    assert np.allclose(expected_state.velocity,new_state.velocity)
    assert np.allclose(expected_state.acceleration,new_state.acceleration)


if __name__ == "__main__":

    test_state = State(position=np.array([1, 1, 1]))
    test_dynamic = TwoBody(mu=1)

    test_two_body_math(default_state=test_state, default_two_body=test_dynamic)
