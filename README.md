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
