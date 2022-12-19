#pragma once
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
    virtual void visit(const Variable* var) = 0;
    virtual void visit(const MultiStmt* var) = 0;
    virtual void visit(const ConstExpr* var) = 0;
    virtual void visit(const SetStmt* var) = 0;
    virtual void visit(const ReturnStmt* var) = 0;
    virtual void visit(const FunctionDef* var) = 0;
};