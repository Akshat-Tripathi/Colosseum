#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "idents.h"

class Expr {}; //Expressions return something
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
public:
    MultiStmt(std::vector<std::unique_ptr<Stmt>>& stmts) : stmts(std::move(stmts)) {}

private:
    std::vector<std::unique_ptr<Stmt>> stmts;
};

class ConstExpr: public Expr {
public:
    ConstExpr(std::string token): token(token) {}

private:
    std::string token;
};

class SetStmt: public Stmt {
public:
    SetStmt(std::unique_ptr<Variable>& lval, std::unique_ptr<Expr>& rval) : lval(std::move(lval)), rval(std::move(rval)) {}

private:
    std::unique_ptr<Variable> lval;
    std::unique_ptr<Expr> rval;
};

class ReturnStmt: public Stmt {
public:
    ReturnStmt(std::unique_ptr<Expr>& rval) : rval(std::move(rval)) {}

private:
    std::unique_ptr<Expr> rval;
};

class FunctionDef: public Stmt {
public:
    FunctionDef(Type return_type,
                 std::string name,
                 std::vector<std::unique_ptr<Variable>>& args,
                 std::optional<std::string> arena,
                 std::unique_ptr<MultiStmt>& body) :
                 return_type(return_type), name(name),
                 args(std::move(args)), arena(arena), body(std::move(body)) {}

private:
    Type return_type;
    std::string name;
    std::vector<std::unique_ptr<Variable>> args;
    std::optional<std::string> arena;
    std::unique_ptr<MultiStmt> body;
};