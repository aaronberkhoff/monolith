"""
Module that defines the agent class
"""

from datetime import datetime, timedelta
from monolith.utils import DATESTR


class Agent:
    """
    Base class for agents in the simulation.

    Attributes
    ----------
    state : State
        The current state of the agent.
    state_data : list
        A list to store the state data of the agent.
    start_time : datetime
        The start time of the simulation.
    """

    def __init__(
        self,
        state,
        start_time,
        duration,
        dt,
        dynamics,
        coefficient_of_drag=None,
        mass=None,
        area=None,
        name="Agent",
        bus=None,  # Allow passing a bus object to the agent, default is None
    ):
        """
        Initializes the Agent with the given parameters.

        Parameters
        ----------
        state : State
            The initial state of the agent.
        start_time : datetime
            The start time of the simulation.
        duration : timedelta, dict
            The duration of the simulation.
        dt : timedelta, dict
            The time step of the simulation.
        coefficient_of_drag : float, optional
            The coefficient of drag of the agent (default is None).
        mass : float, optional
            The mass of the agent (default is None).
        area : float, optional
            The area of the agent (default is None).

        """
        if isinstance(start_time, str):
            start_time = datetime.strptime(start_time, DATESTR)

        if isinstance(duration, dict):
            duration = timedelta(**duration)

        if isinstance(dt, dict):
            dt = timedelta(**dt)

        if area is not None:
            self.area = area * (1e-6)

        self.state = state
        self.start_time = start_time
        self.duration = duration
        self.dt = dt
        self.coefficient_of_drag = coefficient_of_drag
        self.mass = mass

        self.name = name
        self.state_data = []
        self.time_data = []
        self.dynamics = sum(dynamics)
        self.bus = bus  # Allow passing a bus object to the agent, default is None

        pass
