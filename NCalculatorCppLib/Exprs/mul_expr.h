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
	class mul_expr : public bin_expr
	{
	public:
		mul_expr(token op, expr *left, expr *right);

		double eval() override;
	};
}
