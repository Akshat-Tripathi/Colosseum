#pragma once
#include <vector>
#include "types.h"

class Expr {
public:
    virtual Expr() = 0;
};

class Atom: public Expr {
public:
    Atom(string token): name(token) {}

private:
    string name;
};

class Variable: public Atom {
public:
    Variable(string name, Type type, Expr& val): Atom(name), type(type), value(val) {}

private:
    Type type;
    Expr& value;
}

class MultiExpr: public Expr {
    MultiExpr(std::vector<Expr&> exprs) : exprs(exprs) {}
private:
    vector<Expr&> exprs;
};
