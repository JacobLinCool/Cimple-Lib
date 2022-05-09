# Run Container
docker run -dit -v $PWD:/usr/workspace -w /usr/workspace --name cimple-lib-container cimple-lib

# Enter Interactive Shell
docker exec -it cimple-lib-container bash

# Stop Container
docker stop cimple-lib-container

# Remove Container
docker rm cimple-lib-container
