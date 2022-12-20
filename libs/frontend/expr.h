#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "idents.h"
#include "visitor.h"

struct Expr {
    virtual void accept(Visitor& visitor) = 0;
}; //Expressions return something
struct Stmt {
    virtual void accept(Visitor& visitor) = 0;
}; //Statements don't

struct Variable: public Stmt {
    Variable(std::string name, Type type, Location location): name(name), type(type), location(location) {}

    void accept(Visitor& visitor) override {
        visitor.visit(this);
    }

    std::string name;
    Location location;
    Type type;
};

struct MultiStmt: public Stmt {
    MultiStmt(std::vector<std::unique_ptr<Stmt>>& stmts) : stmts(std::move(stmts)) {}

    void accept(Visitor& visitor) override {
        visitor.visit(this);
    }

    std::vector<std::unique_ptr<Stmt>> stmts;
};

struct ConstExpr: public Expr {
    ConstExpr(std::string token): token(token) {}

    void accept(Visitor& visitor) override {
        visitor.visit(this);
    }

    std::string token;
};

struct SetStmt: public Stmt {
    SetStmt(std::unique_ptr<Variable>& lval, std::unique_ptr<Expr>& rval) : lval(std::move(lval)), rval(std::move(rval)) {}

    void accept(Visitor& visitor) override {
        visitor.visit(this);
    }

    std::unique_ptr<Variable> lval;
    std::unique_ptr<Expr> rval;
};

struct ReturnStmt: public Stmt {
    ReturnStmt(std::unique_ptr<Expr>& rval) : rval(std::move(rval)) {}

    void accept(Visitor& visitor) override {
        visitor.visit(this);
    }

    std::unique_ptr<Expr> rval;
};

struct FunctionDef: public Stmt {
    FunctionDef(Type return_type,
                 std::string name,
                 std::vector<std::unique_ptr<Variable>>& args,
                 std::optional<std::string> arena,
                 std::unique_ptr<MultiStmt>& body) :
                 return_type(return_type), name(name),
                 args(std::move(args)), arena(arena), body(std::move(body)) {}

    void accept(Visitor& visitor) override {
        visitor.visit(this);
    }

    Type return_type;
    std::string name;
    std::vector<std::unique_ptr<Variable>> args;
    std::optional<std::string> arena;
    std::unique_ptr<MultiStmt> body;
};