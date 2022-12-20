CC = g++
CC_FLAGS = -g -std=c++17

all: main

bin/sem_check.o: libs/frontend/sem_check.h libs/frontend/sem_check.cpp
	${CC} ${CC_FLAGS} -c libs/frontend/sem_check.cpp -o bin/sem_check.o

bin/parser.o: libs/frontend/parser.h libs/frontend/parser.cpp bin/lexer.o
	${CC} ${CC_FLAGS} -c libs/frontend/parser.cpp -o bin/parser.o

bin/lexer.o: libs/frontend/lexer.h libs/frontend/lexer.cpp
	${CC} ${CC_FLAGS} -c libs/frontend/lexer.cpp -o bin/lexer.o

bin/printer.o: libs/frontend/printer.h libs/frontend/ast_printer.cpp
	${CC} ${CC_FLAGS} -c libs/frontend/ast_printer.cpp -o bin/printer.o

main: bin/lexer.o bin/parser.o bin/printer.o bin/sem_check.o
	${CC} ${CC_FLAGS} main.cpp bin/lexer.o bin/parser.o bin/printer.o bin/sem_check.o -o colosseum

.PHONY: clean

clean:
	rm colosseum
	rm bin/*.o