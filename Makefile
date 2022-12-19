CC = g++
CC_FLAGS = -g -std=c++17

all: main

bin/parser.o: parser.h parser.cpp bin/lexer.o
	${CC} ${CC_FLAGS} -c parser.cpp -o bin/parser.o

bin/lexer.o: lexer.h lexer.cpp
	${CC} ${CC_FLAGS} -c lexer.cpp -o bin/lexer.o

main: bin/lexer.o bin/parser.o
	${CC} ${CC_FLAGS} main.cpp bin/lexer.o bin/parser.o -o colosseum

.PHONY: clean

clean:
	rm colosseum
	rm bin/*.o