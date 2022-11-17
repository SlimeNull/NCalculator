#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	class cond_expr : public expr
	{
	public:
		virtual ~cond_expr()
		{
			delete Condition;
			delete LeftExpr;
			delete RightExpr;
		}

		cond_expr(expr *condition, expr *leftExpr, expr *rightExpr);

		expr *const Condition;
		expr *const LeftExpr;
		expr *const RightExpr;

		double eval() override;

		std::vector<token> enum_tokens() override;
	};
}
