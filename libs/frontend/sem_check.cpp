#include <exception>
#include <frontend/sem_check.h>

void SemCheck::check(const MultiStmt* node) {
    visit(node);
    if (!has_main) {
        throw std::runtime_error("No main function found");
    }
}

void SemCheck::visit(const MultiStmt* node) {
    for (auto& stmt : node->stmts) {
        stmt->accept(*this);
    }
}

// Todo check variables
void SemCheck::visit(const FunctionDef* node) {
    auto& ctx = ctxs.top();
    if (ctx.in_func) {
        throw std::runtime_error("Nested function definitions aren't currently supported");
    }
    has_main = true;

    Context new_ctx(ctx);
    new_ctx.in_func = true;
    new_ctx.return_type = node->return_type;
    ctxs.push(std::move(new_ctx));

    node->body->accept(*this);

    new_ctx = ctxs.top();
    ctxs.pop();
    if (!new_ctx.returned) {
        throw std::runtime_error("Function: " + node->name + " doesn't return");
    }
}

void SemCheck::visit(const ReturnStmt* node) {
    auto& ctx = ctxs.top();
    if (!ctx.in_func) {
        throw std::runtime_error("Return outside of function");
    }
    //TODO: Typecheck the rval
    ctx.returned = true;
}

// Don't do anything right now - TODO fill 
void SemCheck::visit(const ConstExpr* node) {}
