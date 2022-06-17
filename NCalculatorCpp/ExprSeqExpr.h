#pragma once
#include <vector>
#include "Expr.h"
class ExprSeqExpr :
    public Expr
{

public:
    std::vector<Expr> SeqValue;
    ExprSeqExpr(std::vector<Expr>& exprs);
    double eval();

    Expr& operator[] (int index);
};

