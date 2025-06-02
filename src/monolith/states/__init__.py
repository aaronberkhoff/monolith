"""
State object definition and useful functions

"""

from collections.abc import Iterable

import torch

ECI = "J2000"
ECEF = "ITRF93"


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

    _supported_attributes = ["position", "velocity", "acceleration", "time", "lat"]

    def __init__(self, frame="inertial", **kwargs):
        """
        Constructs all the necessary attributes for the State object.
        """
        for key, value in kwargs.items():

            if key in State._supported_attributes:

                if isinstance(value, (Iterable, float, int)):
                    value = torch.tensor(value).view(3, 1)

                setattr(self, key, value)
            else:
                raise ValueError(f"kwarg <{key}> is not supported")

        self.frame = frame

    def place_holder(self, x):
        """
        Placeholder
        """

        return True, x

    def place_holder2(self, x):
        """
        Place holder
        """

        return True, x
