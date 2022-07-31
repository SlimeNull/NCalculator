#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	class EqExpr : public Expr
	{
	public:
		virtual ~EqExpr()
		{
			delete LeftExpr;
			delete RightExpr;
		}

		EqExpr(Token operator_Keyword, Expr *leftExpr, Expr *rightExpr);

		const Token Operator;
		Expr *const LeftExpr;
		Expr *const RightExpr;

		double Eval() override;

		std::vector<Token> EnumTokens() override;
	};
}
