#pragma once

#include "Expr.h"
#include "../Token.h"
#include "MulExpr.h"
#include "PlusExpr.h"
#include <vector>

using namespace NCalculator;

namespace NCalculatorLibExprs
{
	class BinExpr : public Expr
	{
	public:
		const Token Operator;
		Expr *const LeftExpr;
		Expr *const RightExpr;

		virtual ~BinExpr()
		{
			delete LeftExpr;
			delete RightExpr;
		}

		BinExpr(Token op, Expr *left, Expr *right);

		static MulExpr *SpinExpr(MulExpr *expr);

		static PlusExpr *SpinExpr(PlusExpr *expr);

		std::vector<Token> EnumTokens() override;
	};
}
