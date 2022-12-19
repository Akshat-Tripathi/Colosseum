#pragma once
#include <vector>
#include <memory>
#include "expr.h"
#include "lexer.h"

std::unique_ptr<MultiStmt> parse(const List& list);
