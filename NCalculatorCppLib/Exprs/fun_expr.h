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
	class FunExpr : public Expr
	{
	public:
		const Token Func;
		ExprSeqExpr *const Params;

		virtual ~FunExpr()
		{
			delete Params;
		}

		FunExpr(Token func, ExprSeqExpr *param);

		std::vector<Token> EnumTokens() override;

		double Eval() override;
	};
}
