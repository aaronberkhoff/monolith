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

- TODO: Set up docker image for faster CI/CD
