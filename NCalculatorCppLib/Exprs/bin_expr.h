#pragma once

#include "Expr.h"
#include "../Token.h"
#include "MulExpr.h"
#include "PlusExpr.h"
#include <vector>

using namespace NCalculator;

namespace NCalculatorLibExprs
{
	class bin_expr : public expr
	{
	public:
		const token Operator;
		expr *const LeftExpr;
		expr *const RightExpr;

		virtual ~bin_expr()
		{
			delete LeftExpr;
			delete RightExpr;
		}

		bin_expr(token op, expr *left, expr *right);

		static mul_expr *SpinExpr(mul_expr *expr);

		static PlusExpr *SpinExpr(PlusExpr *expr);

		std::vector<token> enum_tokens() override;
	};
}
