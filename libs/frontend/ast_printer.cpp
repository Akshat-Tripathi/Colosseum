#include "printer.h"

void ASTPrinter::visit(const ConstExpr* node) {
        std::cout << "(ConstExpr " << node->token << ')';
    }

void ASTPrinter::visit(const MultiStmt* node) {
    std::cout << "(MultiStmt";
    indents++;
    for (auto& stmt : node->stmts) {
        std::cout << std::endl;
        print_indents();
        stmt->accept(*this);
    }
    indents--;
    std::cout << std::endl;
    print_indents();
    std::cout << ")" << std::endl;
}

void ASTPrinter::visit(const ReturnStmt* node) {
    std::cout << "(ReturnStmt ";
    node->rval->accept(*this);
    std::cout << ')';
}

//TODO do this one properly
void ASTPrinter::visit(const FunctionDef* node) {
    std::cout << "(FunctionDef " << node->return_type.to_string() << ' ' << node->name << ' ';

    std::string hack = "(";
    for (auto& arg : node->args) {
        std::cout << hack;
        arg->accept(*this);
        hack = ", ";
    }
    if (node->args.size() == 0) {
        std::cout << '(';
    }

    std::cout << ") " << node->arena.to_string() << std::endl;;

    indents++;
    print_indents();
    node->body->accept(*this);
    indents--;
    print_indents();
    std::cout << ')' << std::endl;;
}

void ASTPrinter::visit(const Variable* node) {
    std::cout << '(' << node->type.to_string() << ' ' << node->name << ' ' << node->location.to_string() << ')';
}
