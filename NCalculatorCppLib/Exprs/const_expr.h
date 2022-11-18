#pragma once

#include "Expr.h"
#include "../Token.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <functional>
#include "../stringhelper.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{
	class const_expr : public expr
	{
	public:
		const std::wstring Name;
		const_expr(const std::wstring &name);

		static double GetConst(const std::wstring &name);

		std::vector<token> enum_tokens() override;

		double eval() override;
	};
}
