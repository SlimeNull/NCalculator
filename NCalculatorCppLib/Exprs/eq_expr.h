#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
    class eq_expr : public expr
    {
        public:
        virtual ~eq_expr()
        {
            delete LeftExpr;
            delete RightExpr;
        }

        eq_expr(token operator_Keyword, expr* leftExpr, expr* rightExpr);

        const token Operator;
        expr* const LeftExpr;
        expr* const RightExpr;

        double eval() override;

        std::vector<token> enum_tokens() override;
    };
}
