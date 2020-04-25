FROM debian:stretch
LABEL maintainer="Ubicoin Developers <dev@ubicoin.org>"
LABEL description="Dockerised UbicoinCore, built from Travis"

RUN apt-get update && apt-get -y upgrade && apt-get clean && rm -fr /var/cache/apt/*

COPY bin/* /usr/bin/
