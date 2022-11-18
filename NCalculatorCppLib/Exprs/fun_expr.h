#pragma once

#include "Expr.h"
#include "../Token.h"
#include "ExprSeqExpr.h"
#include <vector>
#include <stdexcept>
#include "../stringhelper.h"

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	/// <summary>
	/// id quote_expr
	/// </summary>
	class FunExpr : public expr
	{
	public:
		const token Func;
		expr_seq_expr *const Params;

		virtual ~FunExpr()
		{
			delete Params;
		}

		FunExpr(token func, expr_seq_expr *param);

		std::vector<token> enum_tokens() override;

		double eval() override;
	};
}
