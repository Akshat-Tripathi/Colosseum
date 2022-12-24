CC = g++
CC_FLAGS = -g -std=c++17 -I./libs/ -I/usr/include/llvm-10/ -I/usr/include/llvm-c-10/
LD_FLAGS := $(shell llvm-config --ldflags --libs)


all: main

bin/sem_check.o: libs/frontend/sem_check.h libs/frontend/sem_check.cpp
	${CC} ${CC_FLAGS} -c libs/frontend/sem_check.cpp -o bin/sem_check.o

bin/parser.o: libs/frontend/parser.h libs/frontend/parser.cpp bin/lexer.o
	${CC} ${CC_FLAGS} -c libs/frontend/parser.cpp -o bin/parser.o

bin/lexer.o: libs/frontend/lexer.h libs/frontend/lexer.cpp
	${CC} ${CC_FLAGS} -c libs/frontend/lexer.cpp -o bin/lexer.o

bin/printer.o: libs/general/printer.h libs/general/ast_printer.cpp
	${CC} ${CC_FLAGS} -c libs/general/ast_printer.cpp -o bin/printer.o

bin/llvm_emitter.o: libs/backend/llvm_emitter.h libs/backend/llvm_emitter.cpp
	${CC} ${CC_FLAGS} -c libs/backend/llvm_emitter.cpp -o bin/llvm_emitter.o

bin/main.o: main.cpp bin/sem_check.o bin/parser.o bin/lexer.o bin/printer.o bin/llvm_emitter.o
	${CC} ${CC_FLAGS} -c main.cpp -o main.o

main: bin/main.o bin/lexer.o bin/parser.o bin/printer.o bin/sem_check.o bin/llvm_emitter.o
	${CC} ${CC_FLAGS} main.o bin/lexer.o bin/parser.o bin/printer.o bin/sem_check.o bin/llvm_emitter.o ${LD_FLAGS} -o colosseum

.PHONY: clean

clean:
	rm bin/*.o
	rm colosseum