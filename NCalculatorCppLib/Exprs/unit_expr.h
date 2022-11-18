#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	/// <summary>
	/// basic unit
	/// 
	/// | num
	/// | fun_expr
	/// | quote_expr
	/// </summary>
	class UnitExpr : public expr
	{
	public:
		const bool Signed;
		expr *const Value;

		virtual ~UnitExpr()
		{
			delete Value;
		}

		UnitExpr(expr *value, bool signed_Keyword);

		std::vector<token> enum_tokens() override;

		double eval() override;
	};
}
