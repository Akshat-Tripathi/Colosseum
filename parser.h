#pragma once
#include <vector>
#include <memory>
#include "expr.h"
#include "lexer.h"

std::vector<std::unique_ptr<Stmt>> parse(List& list);
