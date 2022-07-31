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
	class UnitExpr : public Expr
	{
	public:
		const bool Signed;
		Expr *const Value;

		virtual ~UnitExpr()
		{
			delete Value;
		}

		UnitExpr(Expr *value, bool signed_Keyword);

		std::vector<Token> EnumTokens() override;

		double Eval() override;
	};
}
