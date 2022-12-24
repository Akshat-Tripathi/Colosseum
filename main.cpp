#include <iostream>
#include <fstream>
#include <frontend/lexer.h>
#include <frontend/parser.h>
#include <frontend/sem_check.h>
#include <general/printer.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Please enter the filename" << std::endl;
        return 1;
    }

    std::ifstream file;
    file.open(argv[1]);

    const auto lexed = lex(file);
    print(lexed);

    auto parsed = parse(*lexed);

    ASTPrinter printer(std::cout);
    printer.print(parsed.get());

    SemCheck checker;

    checker.check(parsed.get());

    file.close();
    return 0;
}
