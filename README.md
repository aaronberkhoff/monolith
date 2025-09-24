remember to inlcude pybind11-stubgen

# GitHub workflow testing
- `brew install act`
- `act -j build`

# Docker
- `sudo docker ps -a`
Stop Container
- `docker stop $(docker ps -aq)`
- `docker rm $(docker ps -aq)`
- `docker image prune -a`
- `docker volume prune`
- `docker network prune`
- `act push -s PYPI_API_TOKEN=yourtoken`

- TODO: Set up docker image for faster CI/CD

- Left off with bindings
- NEED to refactor makefile to produce .so in python and one .o in obj
- Need to figure out stubes with name spaces

## Naming Convention

In Monolith, we follow a **consistent, units-aware naming convention** to improve readability, maintainability, and code clarity across all physics and astrodynamics modules.

### Rules

1. **Unit-based variables**
   - For variables that represent measurable quantities (length, time, mass, velocity, density, etc.), the **unit or physical concept goes first**, followed by its qualifier.
   - Examples:
     - `altitude_reference` – the reference altitude of an atmospheric layer
     - `time_epoch` – the epoch time of a state
     - `velocity_initial` – the initial velocity vector
     - `density_reference` – reference density for a given altitude

2. **Domain/concept objects**
   - For objects representing entities, models, or concepts without a direct physical unit, use **natural English order**.
   - Examples:
     - `central_body` – the primary celestial body for orbital calculations
     - `target_body` – a secondary body or target
     - `gravity_model` – the chosen gravitational model

### Benefits

- **Readability**: Unit-based variables are grouped by physical dimension, making it easier to scan structs and tables.
- **Consistency**: All measured quantities follow a predictable `unit_qualifier` pattern.
- **Maintainability**: Domain objects retain natural names, avoiding awkward or confusing names like `body_central`.
- **Editor-friendly**: Autocomplete and table layouts naturally group related variables together.

By following this convention, developers can quickly understand the purpose and type of a variable just from its name, reducing errors and improving the clarity of physics-intensive code.
