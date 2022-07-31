#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	class CondExpr : public Expr
	{
	public:
		virtual ~CondExpr()
		{
			delete Condition;
			delete LeftExpr;
			delete RightExpr;
		}

		CondExpr(Expr *condition, Expr *leftExpr, Expr *rightExpr);

		Expr *const Condition;
		Expr *const LeftExpr;
		Expr *const RightExpr;

		double Eval() override;

		std::vector<Token> EnumTokens() override;
	};
}
