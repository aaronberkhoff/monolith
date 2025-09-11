"""
module for dynamics
"""

import torch


class Dynamic:
    def __init__(self, func=None):
        self._func = func if func is not None else self.func

    def __call__(self, state):
        return self._func(state)

    def __add__(self, other):
        if not isinstance(other, Dynamic):
            raise TypeError(
                f"Cannot add object of type <{type(other)}> to type Dynamic"
            )

        return CombinedDynamics(self, other)

    def __radd__(self, other):
        if other == 0:
            return self
        return self.__add__(other)

    def func(self, state):
        return torch.zeros_like(state)  # Default: no dynamics


class CombinedDynamics(Dynamic):

    def __init__(self, *dynamics):
        super().__init__()
        self.dynamics = dynamics

    def func(self, state):

        for dyn in self.dynamics:

            state @= dyn(state)
