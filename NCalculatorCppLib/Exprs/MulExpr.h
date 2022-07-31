#pragma once

#include "BinExpr.h"
#include "../Token.h"
#include "Expr.h"

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	/// <summary>
	/// multiply expression
	/// 
	/// | unit * | / | % | ^ mul_expr
	/// | unit * | / | % | ^ unit
	/// </summary>
	class MulExpr : public BinExpr
	{
	public:
		MulExpr(Token op, Expr *left, Expr *right);

		double Eval() override;
	};
}
