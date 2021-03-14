FROM ubuntu:latest as executor

RUN apt-get update && \
    apt-get -y install --no-install-recommends \
    make \
    g++ \
    cmake

WORKDIR /app

COPY . /app

RUN mkdir build && \
    cd build && \
    cmake .. && \
    make

WORKDIR /app/build

ENTRYPOINT [ "/app/build/MyProject" ]