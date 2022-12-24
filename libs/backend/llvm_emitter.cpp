#include <backend/llvm_emitter.h>

#include <llvm/IR/IRBuilder.h>

void LLVMEmitter::emit(const MultiStmt* node) {
    visit(node);
}
