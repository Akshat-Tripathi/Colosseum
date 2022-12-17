#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "idents.h"

class Expr {};

class Variable: public Expr {
public:
    Variable(std::string name, Type type, Location location): name(name), type(type), location(location) {}

private:
    std::string name;
    Location location;
    Type type;
};

class MultiExpr: public Expr {
    MultiExpr(std::vector<std::unique_ptr<Expr>> exprs) : exprs(std::move(exprs)) {}

private:
    std::vector<std::unique_ptr<Expr>> exprs;
};

class ConstExpr: public Expr {
public:
    ConstExpr(std::string token): token(token) {}

private:
    std::string token;
};

class Noop: public Expr {};

class SetExpr: public Expr {
public:
    SetExpr(Variable& lval, Expr& rval) : lval(lval), rval(rval) {}

private:
    Variable& lval;
    Expr& rval;
};

class ReturnExpr: public Expr {
public:
    ReturnExpr(Expr& rval) : rval(rval) {}

private:
    Expr& rval;
};

class FunctionExpr: public Expr {
public:
    FunctionExpr(Type return_type,
                 std::string name,
                 std::vector<std::unique_ptr<Variable>> args,
                 std::optional<std::string> arena) :
                 return_type(return_type), name(name),
                 args(std::move(args)), arena(arena) {}

private:
    Type return_type;
    std::string name;
    std::vector<std::unique_ptr<Variable>> args;
    std::optional<std::string> arena;
};