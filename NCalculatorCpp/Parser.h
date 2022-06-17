#pragma once
#include <vector>
#include "Token.h"
#include "Expr.h"

std::vector<Expr> parse(std::vector<Token>& tokens);