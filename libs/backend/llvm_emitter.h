#pragma once

#include <ostream>
#include <general/ast.h>
#include <backend/emitter.h>

class LLVMEmitter : public AbstractEmitter {
public:
    LLVMEmitter(std::ostream& stream) : AbstractEmitter(stream) {}

    void emit(const MultiStmt* node);

private:
    void visit(const ConstExpr* node) {}
    void visit(const MultiStmt* node) {}
    void visit(const ReturnStmt* node) {}
    void visit(const FunctionDef* node) {}
    void visit(const Variable* node) {}
    void visit(const SetStmt* node) {}
};