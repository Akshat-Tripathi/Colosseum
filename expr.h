#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "idents.h"

class Stmt {}; //Expressions return something
class Stmt {}; //Statements don't


class Variable: public Stmt {
public:
    Variable(std::string name, Type type, Location location): name(name), type(type), location(location) {}

private:
    std::string name;
    Location location;
    Type type;
};

class MultiStmt: public Stmt {
    MultiStmt(std::vector<std::unique_ptr<Stmt>> exprs) : exprs(std::move(exprs)) {}

private:
    std::vector<std::unique_ptr<Stmt>> exprs;
};

class ConstExpr: public Stmt {
public:
    ConstExpr(std::string token): token(token) {}

private:
    std::string token;
};

class SetStmt: public Stmt {
public:
    SetStmt(Variable& lval, Stmt& rval) : lval(lval), rval(rval) {}

private:
    Variable& lval;
    Stmt& rval;
};

class ReturnStmt: public Stmt {
public:
    ReturnStmt(Stmt& rval) : rval(rval) {}

private:
    Stmt& rval;
};

class FunctionDef: public Stmt {
public:
    FunctionDef(Type return_type,
                 std::string name,
                 std::vector<std::unique_ptr<Variable>> args,
                 std::optional<std::string> arena,
                 std::unique_ptr<MultiStmt> body) :
                 return_type(return_type), name(name),
                 args(std::move(args)), arena(arena), body(std::move(body)) {}

private:
    Type return_type;
    std::string name;
    std::vector<std::unique_ptr<Variable>> args;
    std::optional<std::string> arena;
    std::unique_ptr<MultiStmt> body;
};