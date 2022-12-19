CC = g++
CC_FLAGS = -g -std=c++17

all: main

bin/parser.o: libs/frontend/parser.h libs/frontend/parser.cpp bin/lexer.o
	${CC} ${CC_FLAGS} -c libs/frontend/parser.cpp -o bin/parser.o

bin/lexer.o: libs/frontend/lexer.h libs/frontend/lexer.cpp
	${CC} ${CC_FLAGS} -c libs/frontend/lexer.cpp -o bin/lexer.o

main: bin/lexer.o bin/parser.o
	${CC} ${CC_FLAGS} main.cpp bin/lexer.o bin/parser.o -o colosseum

.PHONY: clean

clean:
	rm colosseum
	rm bin/*.o