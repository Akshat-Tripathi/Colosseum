#pragma once
#include <vector>
#include <memory>
#include <frontend/lexer.h>
#include <general/ast.h>

std::unique_ptr<MultiStmt> parse(const List& list);
