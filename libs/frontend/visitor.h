#pragma once
#include <iostream>
#include "expr.h"

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
