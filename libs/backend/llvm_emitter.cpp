#include <backend/llvm_emitter.h>

#include <exception>
#include <vector>

#include <general/idents.h>

#include <llvm/IR/Value.h>
#include <llvm/IR/Constant.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Verifier.h>

void LLVMEmitter::emit(const MultiStmt* node) {
    llvm::BasicBlock *BB = llvm::BasicBlock::Create(ctx);
    builder.SetInsertPoint(BB);
    visit(node);

    if (!llvm::verifyModule(mod, &llvm::errs())) {
        std::string str;
        llvm::raw_string_ostream sstream(str);
        mod.print(sstream, nullptr);

        stream << str;
    }
}

void LLVMEmitter::visit(const ConstExpr* node) {
    if (node->type == Type::Int()) {
        push(llvm::ConstantInt::get(ctx, llvm::APInt(32, std::get<int>(node->val), true))); //Default ints are int32_ts
    } else {
        throw std::runtime_error("Unreachable");
    }
}


void LLVMEmitter::visit(const ReturnStmt* node) {
    node->rval->accept(*this);
    llvm::Value* val = pop();

    push(builder.CreateRet(val));
}

// PRE: A basic block has been setup before this has been called
void LLVMEmitter::visit(const MultiStmt* node) {
    for (auto& stmt : node->stmts) {
        stmt->accept(*this);
    }
}

void LLVMEmitter::visit(const FunctionDef* node) {
    //TODO: this
    std::vector<llvm::Type*> arg_types;

    //TODO: more than just ints
    auto* ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(ctx), arg_types, false);
    
    //TODO: public vs private maybe?
    auto* func = llvm::Function::Create(ft, llvm::Function::ExternalLinkage, node->name, mod);

    llvm::BasicBlock *bb = llvm::BasicBlock::Create(ctx, "entry", func);
    builder.SetInsertPoint(bb);
    node->body->accept(*this);

    llvm::verifyFunction(*func, &llvm::errs()); //TODO add error checking
}
