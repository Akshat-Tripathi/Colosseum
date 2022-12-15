CC = g++
CC_FLAGS = -g

all: main

main:
	${CC} ${CC_FLAGS} main.cpp -o colosseum

.PHONY: clean

clean:
	rm colosseum
	rm bin/*.o