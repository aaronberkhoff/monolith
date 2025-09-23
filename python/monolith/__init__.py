"""
Monolith: Python bindings for orbital dynamics and planetary models.
"""

from importlib import import_module

# Load compiled extensions
dynamics = import_module("monolith.dynamics")
celestial_bodies = import_module("monolith.celestial_bodies")
time = import_module("monolith.time")

__all__ = ["dynamics", "celestial_bodies", "time"]
