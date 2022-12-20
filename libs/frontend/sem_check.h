#pragma once
#include <stack>
#include "expr.h"
#include "idents.h"
#include "visitor.h"

class SemCheck : public Visitor {
public:

    SemCheck() {
        ctxs.push({Type::Int(), false, false});
    }

    void check(const MultiStmt* node);

private:
    void visit(const MultiStmt* node);
    void visit(const ConstExpr* node);
    void visit(const ReturnStmt* node);
    void visit(const FunctionDef* node);
    
    void visit(const Variable* node) {}
    void visit(const SetStmt* node) {} // TODO fill in
    struct Context {
        Type return_type;
        bool in_func;
        bool returned;
    };

    std::stack<Context> ctxs;
    bool has_main;
};
