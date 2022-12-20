#pragma once
#include "expr.h"

class ASTPrinter : public Visitor {
public:

    ASTPrinter() : indents(0) {}

    void visit(const ConstExpr* node);

    void visit(const MultiStmt* node);

    void visit(const ReturnStmt* node);

    //TODO do this one properly
    void visit(const FunctionDef* node);

    void visit(const SetStmt* node) {}
    void visit(const Variable* node) {}

private:
    void print_indents() {
        for (int i = 0; i < indents; i++) {
            std::cout << '\t';
        }
    }

    int indents;
};
