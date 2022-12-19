#include <iostream>
#include <fstream>
#include "lexer.h"
#include "parser.h"

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

    file.close();
    return 0;
}
