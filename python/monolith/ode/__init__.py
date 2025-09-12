"""

Module that holds Base ODE class and methods

"""

import torch


class ODE:

    def __init__(self, agents):

        self.agents = agents
        self.functions = [agent.dynamic for agent in agents]

        pass

    def solve(self):

        pass
