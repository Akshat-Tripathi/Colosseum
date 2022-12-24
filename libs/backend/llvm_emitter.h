#pragma once

#include <ostream>
#include <memory>
#include <stack>

#include <general/ast.h>
#include <backend/emitter.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

class LLVMEmitter : public AbstractEmitter {
public:
    LLVMEmitter(std::ostream& stream) : AbstractEmitter(stream), builder(ctx), mod("default", ctx) {}
    void emit(const MultiStmt* node);

private:
    void visit(const ConstExpr* node);
    void visit(const MultiStmt* node);
    void visit(const ReturnStmt* node);
    void visit(const FunctionDef* node);
    void visit(const Variable* node) {}
    void visit(const SetStmt* node) {}

    llvm::LLVMContext ctx;
    llvm::Module mod;
    llvm::IRBuilder<> builder;

    // Used to allow us to return values even though the visitor returns void
    std::stack<llvm::Value*> value_stack;

    // Helpers because stack is dumb
    void push(llvm::Value* val) {
        value_stack.push(val);
    }

    llvm::Value* pop() {
        llvm::Value* val = value_stack.top();
        value_stack.pop();
        return val;
    }
};