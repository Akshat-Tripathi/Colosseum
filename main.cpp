#include <iostream>
#include <fstream>
#include "lexer.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }
    std::string fname = argv[1];
    std::ifstream file;
    // file.open("test/good/code/return_0.col");
    file.open(fname);

    auto lexed = lex(file);

    print(lexed);

    file.close();
    return 0;
}
