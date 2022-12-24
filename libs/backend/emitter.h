#pragma once

#include <ostream>
#include <general/visitor.h>
#include <general/ast.h>

class AbstractEmitter : public Visitor {
public:
    AbstractEmitter(std::ostream& stream) : stream(stream) {}

    virtual void emit(const MultiStmt* node) = 0;

private:
    std::ostream& stream;
};
