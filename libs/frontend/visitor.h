#pragma once
#include <iostream>

//Forward declare everything
class Variable;
class MultiStmt;
class ConstExpr;
class SetStmt;
class ReturnStmt;
class FunctionDef;

class Visitor {
public:
    virtual void visit(const Variable* node) = 0;
    virtual void visit(const MultiStmt* node) = 0;
    virtual void visit(const ConstExpr* node) = 0;
    virtual void visit(const SetStmt* node) = 0;
    virtual void visit(const ReturnStmt* node) = 0;
    virtual void visit(const FunctionDef* node) = 0;
};

#include "expr.h" // Needed for printing to work because this file and expr have a circular dependency - TODO fix

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
