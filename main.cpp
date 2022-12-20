#include <iostream>
#include <fstream>
#include "libs/frontend/lexer.h"
#include "libs/frontend/parser.h"
#include "libs/frontend/printer.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Please enter the filename" << std::endl;
        return 1;
    }

    std::ifstream file;
    file.open(argv[1]);

    const auto lexed = lex(file);
    // print(lexed);

    auto parsed = parse(*lexed);

    ASTPrinter printer(std::cout);
    printer.visit(parsed.get());

    file.close();
    return 0;
}
