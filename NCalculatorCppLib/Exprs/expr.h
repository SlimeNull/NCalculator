#pragma once

#include "../Token.h"
#include <string>
#include <vector>



using namespace NCalculatorLib;
using namespace NCalculator;

namespace NCalculatorLibExprs
{
	class Expr
	{
	public:
		virtual double Eval() = 0;
		virtual std::vector<Token> EnumTokens() = 0;

		std::wstring ToString();
	};
}
