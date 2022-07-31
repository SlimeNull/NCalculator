#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	class RelExpr : public Expr
	{
	public:
		virtual ~RelExpr()
		{
			delete LeftExpr;
			delete RightExpr;
		}

		RelExpr(Token opt, Expr *leftExpr, Expr *rightExpr);

		const Token Operator;
		Expr *const LeftExpr;
		Expr *const RightExpr;

		double Eval() override;

		std::vector<Token> EnumTokens() override;
	};
}
