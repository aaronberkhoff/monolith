"""
Author: Aaron Berkhoff:

"""

from typing import Optional
from datetime import datetime
import torch


class State:
    """
    Object that stores state information:

    Attributes:
    ----------
        position: torch tensor (3,1), optional
        velocity: torch tensor (3,1), optional
        acceleration: torch tensor (3,1), optional
        attitude: torch tensor (4,1) or (3,1), optional
        angular_velocity: torch tensor (3,1), optional
        angular_acceleration: torch tensor (3,1), optional
        latitude: torch tensor (1,1)
        longitude: torch tensor (1,1)
        altitude: torch tensor
        time: datetime, optional
        frame: str, optional:
            The reference frame of the state ('inertial' or 'ECEF', default is 'inertial').
        orbital_elements: monolith.orbital_elements, optional
    """

    position: Optional[torch.Tensor]
    velocity: Optional[torch.Tensor]
    acceleration: Optional[torch.Tensor]
    attitude: Optional[torch.Tensor]
    angular_velocity: Optional[torch.Tensor]
    angular_acceleration: Optional[torch.Tensor]
    latitude: Optional[torch.Tensor]
    longitude: Optional[torch.Tensor]
    altitude: Optional[torch.Tensor]
    time: Optional[datetime]
    orbital_elements: Optional[object]  # Replace with actual type if you have it

    _supported_attributes = [
        "position",
        "velocity",
        "acceleration",
        "attitude",
        "angular_velocity",
        "angular_acceleration",
        "latitude",
        "longitude",
        "altitude",
        "time",
        "orbital_elements",
    ]

    def __init__(self, frame="inertial", **kwargs):

        # Initialize all known attributes to None
        for attr in self._supported_attributes:
            setattr(self, attr, None)

        # Set attributes passed via kwargs
        for key, value in kwargs.items():
            if key in State._supported_attributes:
                if isinstance(value, (list, tuple, float, int)):
                    value = torch.tensor(value).view(-1, 1)
                setattr(self, key, value)
            else:
                raise ValueError(f"kwarg <{key}> is not supported")

        self.frame = frame

    def get_full_state(self) -> torch.Tensor:
        """
        Concatenates all available tensor attributes in the documented order
        into a single (N, 1) torch tensor.

        Order:
            position, velocity, acceleration, attitude,
            angular_velocity, angular_acceleration,
            latitude, longitude, altitude

        Returns:
            torch.Tensor: Concatenated state vector.
        """
        ordered_attrs = [
            "position",
            "velocity",
            "acceleration",
            "attitude",
            "angular_velocity",
            "angular_acceleration",
            "latitude",
            "longitude",
            "altitude",
        ]

        tensors = []

        for attr in ordered_attrs:
            value = getattr(self, attr, None)
            if isinstance(value, torch.Tensor):
                tensors.append(value)

        if tensors:
            return torch.cat(tensors, dim=0)

        raise ValueError("No tensor attributes are set on the State object.")

    def placeholder(self, x):
        """
        Place holder
        """

        return False, x
