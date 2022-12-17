CC = g++
CC_FLAGS = -g -std=c++17

all: main

bin/lexer.o: lexer.cpp
	${CC} ${CC_FLAGS} -c lexer.cpp -o bin/lexer.o

main: bin/lexer.o
	${CC} ${CC_FLAGS} main.cpp bin/lexer.o -o colosseum

.PHONY: clean

clean:
	rm colosseum
	rm bin/*.o