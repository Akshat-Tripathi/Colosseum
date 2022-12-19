#include <iostream>
#include "lexer.h"

int main() {
    auto lexed = lex(std::cin);
    print(lexed);
    return 0;
}
