#include <iostream>
#include <fstream>
#include <frontend/lexer.h>
#include <frontend/parser.h>
#include <frontend/sem_check.h>
#include <general/printer.h>
#include <backend/llvm_emitter.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Please enter the input and output filenames" << std::endl;
        return 1;
    }

    std::ifstream input;
    input.open(argv[1]);
    
    std::ofstream output;
    output.open(argv[2]);

    const auto lexed = lex(input);
    print(lexed);

    auto parsed = parse(*lexed);

    ASTPrinter printer(std::cout);
    printer.print(parsed.get());

    SemCheck checker;

    checker.check(parsed.get());

    LLVMEmitter emitter(output);

    emitter.emit(parsed.get());

    input.close();
    output.close();
    return 0;
}
