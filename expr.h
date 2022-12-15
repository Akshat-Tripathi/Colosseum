#pragma once
#include <memory>
#include <vector>
#include "types.h"

class Expr {};

class Atom: public Expr {
public:
    Atom(std::string token): name(token) {}

private:
    std::string name;
};

class Variable: public Atom {
public:
    Variable(std::string name, Type type, Expr& val): Atom(name), type(type), value(val) {}

private:
    Type type;
    Expr& value;
};

class MultiExpr: public Expr {
    MultiExpr(std::vector<std::unique_ptr<Expr>> exprs) : exprs(std::move(exprs)) {}

private:
    std::vector<std::unique_ptr<Expr>> exprs;
};
