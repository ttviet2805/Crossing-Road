CPP=g++
FLAGS=-std=c++17 -O2 -Wall -Wconversion
INCLUDE=-I "include"
LIB=-L lib -l sfml-graphics -l sfml-window -l sfml-system -l sfml-audio -l sfml-network

all: compile link

compile:
	${CPP} ${FLAGS} ${INCLUDE} -c *.cpp
	${CPP} ${FLAGS} ${INCLUDE} -c filecpp/*.cpp
link:
	${CPP} *.o -o CrossyRoad ${LIB}