#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	class RelExpr : public expr
	{
	public:
		virtual ~RelExpr()
		{
			delete LeftExpr;
			delete RightExpr;
		}

		RelExpr(token opt, expr *leftExpr, expr *rightExpr);

		const token Operator;
		expr *const LeftExpr;
		expr *const RightExpr;

		double eval() override;

		std::vector<token> enum_tokens() override;
	};
}
