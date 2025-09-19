"""
Unit tests for the dynamics folders

"""
from dataclasses import dataclass
from typing import Optional

import numpy as np
import pytest


from monolith.dynamics import State, TwoBody, J2, J3
from monolith.celestial_bodies import Earth, Moon, CelestialBody

from tests.dynamics.dynamics_oracle import DynamicsOracle

class MockPlanet(CelestialBody):

    def __init__(self):

        mu = 1.0
        j2 = 1.0
        j3 = 1.0
        name = "test"
        radius = 1.0
        spice_id = 404

        super().__init__(name,mu,radius,j2,j3,spice_id)


@dataclass
class MockScenario:

    state: Optional[State] = None
    two_body: Optional[TwoBody] =  None
    j2: Optional[J2] = None
    j3: Optional[J3] = None
    planet: Optional[MockPlanet] = None
    oracle: Optional[DynamicsOracle] = None

def construct_mock_scenario():

    mock_planet = MockPlanet()
    mock_scenario = MockScenario()

    mock_scenario.state = State(position=np.array([1, 1, 1]))
    mock_scenario.j2 = J2(central_body=mock_planet)
    mock_scenario.j3 = J3(central_body=mock_planet)
    mock_scenario.planet = mock_planet
    mock_scenario.two_body = TwoBody(central_body= mock_planet)
    mock_scenario.oracle = DynamicsOracle(state=mock_scenario.state, planet = mock_scenario.planet)

    return mock_scenario


@pytest.fixture
def mock_scenario():
    """Fixture that creates a default scenario"""

    return construct_mock_scenario()



def test_state_initialize(mock_scenario:MockScenario):
    """
    Tests the init of the State class
    """
    #test default values
    assert np.allclose(mock_scenario.state.position,np.array([1,1,1]))
    assert np.allclose(mock_scenario.state.velocity, np.array([0,0,0]))
    assert np.allclose(mock_scenario.state.acceleration, np.array([0,0,0]))



def test_dynamic_initialize(mock_scenario: MockScenario):

    """
    Test the init of the Dynamics class
    """
    #Two body
    assert np.isclose(mock_scenario.two_body.central_body.mu, 1.0, rtol=1e-09, atol=1e-09)

    #J2
    assert np.isclose(mock_scenario.j2.central_body.mu, 1.0)
    assert np.isclose(mock_scenario.j2.central_body.j2, 1.0)
    assert np.isclose(mock_scenario.j2.central_body.j3, 1.0)
    assert np.isclose(mock_scenario.j2.central_body.radius, 1.0)
    assert mock_scenario.j2.central_body.name == "test"
    assert mock_scenario.j2.central_body.spice_id == 404

    #J3
    assert np.isclose(mock_scenario.j3.central_body.mu, 1.0)
    assert np.isclose(mock_scenario.j3.central_body.j2, 1.0)
    assert np.isclose(mock_scenario.j3.central_body.j3, 1.0)
    assert np.isclose(mock_scenario.j3.central_body.radius, 1.0)
    assert mock_scenario.j3.central_body.name == "test"
    assert mock_scenario.j3.central_body.spice_id == 404

def test_two_body_operator(mock_scenario: MockScenario):

    #state operation
    new_state = mock_scenario.two_body(mock_scenario.state)
    assert isinstance(new_state, State)

    #expected behavior for two body
    expected_acceleration = mock_scenario.oracle.get_two_body_acceleration()

    assert np.allclose(mock_scenario.state.position,new_state.position) # position is unchanged
    assert np.allclose(mock_scenario.state.velocity,new_state.velocity) # velocity is unchanged
    assert np.allclose(expected_acceleration,new_state.acceleration)

def test_j2_operator(mock_scenario: MockScenario):

    #state operation
    new_state = mock_scenario.j2(mock_scenario.state)
    assert isinstance(new_state, State)

    #expected behavior for two body
    expected_acceleration = mock_scenario.oracle.get_j2_acceleration()

    assert np.allclose(mock_scenario.state.position,new_state.position) # position is unchanged
    assert np.allclose(mock_scenario.state.velocity,new_state.velocity) # velocity is unchanged
    assert np.allclose(expected_acceleration,new_state.acceleration)

def test_j3_operator(mock_scenario: MockScenario):

    #state operation
    new_state = mock_scenario.j3(mock_scenario.state)
    assert isinstance(new_state, State)

    #expected behavior for two body
    expected_acceleration = mock_scenario.oracle.get_j3_acceleration()

    assert np.allclose(mock_scenario.state.position,new_state.position) # position is unchanged
    assert np.allclose(mock_scenario.state.velocity,new_state.velocity) # velocity is unchanged
    assert np.allclose(expected_acceleration,new_state.acceleration)


if __name__ == "__main__":

    mock_scenario_debug = construct_mock_scenario()

    test_state_initialize(mock_scenario=mock_scenario_debug)
    test_dynamic_initialize(mock_scenario=mock_scenario_debug)
    test_two_body_operator(mock_scenario=mock_scenario_debug)
    test_j2_operator(mock_scenario=mock_scenario_debug)
    test_j3_operator(mock_scenario=mock_scenario_debug)
