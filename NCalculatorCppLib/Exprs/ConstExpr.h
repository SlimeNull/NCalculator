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
	class ConstExpr : public Expr
	{
	public:
		const std::wstring Name;
		ConstExpr(const std::wstring &name);

		static double GetConst(const std::wstring &name);

		std::vector<Token> EnumTokens() override;

		double Eval() override;
	};
}
