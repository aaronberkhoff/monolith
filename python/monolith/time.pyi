"""
Pybind11 bindings for Time Module
"""
from __future__ import annotations
import typing
__all__: list[str] = ['TimeParameter']
class TimeParameter:
    day: int
    hour: int
    microsecond: float
    minute: int
    month: int
    second: int
    year: int
    @typing.overload
    def __init__(self) -> None:
        ...
    @typing.overload
    def __init__(self, year: int, month: int, day: int, hour: int, minute: int, second: int, microsecond: float) -> None:
        ...
    def get_et(self) -> float:
        ...
