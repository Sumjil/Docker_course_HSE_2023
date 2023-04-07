FROM ubuntu:22.04
FROM gcc:latest

COPY . /urs/src/bridges

WORKDIR /urs/src/bridges

RUN g++ -o Find_bridges main.cpp

CMD ["./Find_bridges"]