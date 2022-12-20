#pragma once
#include <ostream>
#include "expr.h"
#include "visitor.h"

class ASTPrinter : public Visitor {
public:

    ASTPrinter(std::ostream& stream) : stream(stream), indents(0) {}

    void visit(const ConstExpr* node);
    void visit(const MultiStmt* node);
    void visit(const ReturnStmt* node);
    void visit(const FunctionDef* node);
    void visit(const Variable* node);
    
    void visit(const SetStmt* node) {}

private:
    void print_indents() {
        for (int i = 0; i < indents; i++) {
            std::cout << '\t';
        }
    }

    int indents;
    std::ostream& stream;
};
