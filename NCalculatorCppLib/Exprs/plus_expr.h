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
	class PlusExpr : public bin_expr
	{
	public:
		PlusExpr(token op, expr *left, expr *right);

		double eval() override;
	};
}
