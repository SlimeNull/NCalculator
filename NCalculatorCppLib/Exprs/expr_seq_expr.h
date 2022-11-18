#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
    //public abstract class Expr
    //{
    //    public abstract double Eval();
    //}

    class expr_seq_expr : public expr
    {
        private:
        std::vector<expr*> SeqValue;

        public:
        expr_seq_expr(std::vector<expr*> exprs);

        expr* operator[](int index);

        double eval() override;

        std::vector<token> enum_tokens() override;
    };
}
