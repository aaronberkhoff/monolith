"""
Unit test for the states folder

"""

import numpy as np
from datetime import datetime
import torch

from monolith.states import State


def test_state_creation():
    """
    Test the creation of the State object
    """

    position = (1, 1, 1)
    velocity = (1, 1, 1)
    date_str = "2025-06-02"
    time = datetime.strptime(date_str, "%Y-%m-%d")

    state = State(position=position, velocity=velocity, time=time)

    # check the right dimensions
    assert state.position.shape == (len(position), 1)
    assert state.velocity.shape == (len(velocity), 1)

    # check if they are the right type and data is the same
    assert state.time == time
    assert torch.equal(state.position, torch.tensor(position).view(3, 1))
    assert torch.equal(state.velocity, torch.tensor(velocity).view(3, 1))


if __name__ == "__main__":

    test_state_creation()
