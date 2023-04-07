FROM ubuntu:22.04
FROM gcc:latest

COPY . /urs/src/games

WORKDIR /urs/src/games

RUN g++ -o Find_bridges main.cpp

CMD ["./Find_bridges"]