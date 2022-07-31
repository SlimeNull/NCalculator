#pragma once

#include "BinExpr.h"
#include "../Token.h"
#include "Expr.h"

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	/// <summary>
	/// add expression
	/// 
	/// | mul + | - plus
	/// | mul + | - mul
	/// | unit + | - plus
	/// | unit + | - mul
	/// | unit - | - unit
	/// </summary>
	class PlusExpr : public BinExpr
	{
	public:
		PlusExpr(Token op, Expr *left, Expr *right);

		double Eval() override;
	};
}
