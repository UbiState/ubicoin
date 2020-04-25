#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-UbiState/ubicoind-develop}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/ubicoind docker/bin/
cp $BUILD_DIR/src/ubicoin-cli docker/bin/
cp $BUILD_DIR/src/ubicoin-tx docker/bin/
strip docker/bin/ubicoind
strip docker/bin/ubicoin-cli
strip docker/bin/ubicoin-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
