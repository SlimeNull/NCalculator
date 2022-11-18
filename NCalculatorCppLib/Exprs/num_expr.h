#pragma once

#include "Expr.h"
#include "../Token.h"
#include <string>
#include <vector>

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	/// <summary>
	/// basic number
	/// 
	/// | num_literal
	/// </summary>
	class NumExpr : public expr
	{
	public:
		const std::wstring Value;

		NumExpr(const std::wstring &value);

		std::vector<token> enum_tokens() override;

		double eval() override;
	};
}
