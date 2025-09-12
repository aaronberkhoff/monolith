import torch

from monolith.dynamics_dep import Dynamic


class TwoBody(Dynamic):
    """
    A class to represent a Keplerian dynamic.

    Attributes
    ----------
    scenario : Scenario
        The scenario of the dynamic.
    agent : Agent
        The agent of the dynamic.
    stm : STM
        The state transition matrix of the dynamic.
    function : function
        The function of the dynamic.
    """

    def __init__(self, central_body):
        super.__init__(self)

        """
        Constructs all the necessary attributes for the Keplerian object.

        Parameters
        ----------
        scenario : Scenario
            The scenario of the dynamic.
        agent : Agent
            The agent of the dynamic.
        stm : STM
            The state transition matrix of the dynamic.

        """

        self.central_body = central_body

    def func(self, state, time: float = None):
        """
        The function of the Keplerian dynamic.

        Parameters
        ----------
        state : State
            The state of the dynamic.
        time : float
            The time of the dynamic.

        Returns
        -------
        State
            The result of the function.
        """

        radius = torch.norm(state[0:3])

        acceleration = -self.central_body.mu * state[0:3] / radius

        dot = torch.stack([state[3:6], acceleration])

        return acceleration
