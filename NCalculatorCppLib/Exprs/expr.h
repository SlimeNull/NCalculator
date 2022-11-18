#pragma once

#include "../Token.h"
#include <string>
#include <vector>



using namespace NCalculator;

namespace NCalculatorLibExprs
{
	class expr
	{
	public:
		virtual double eval() = 0;
		virtual std::vector<token> enum_tokens() = 0;

		std::wstring to_string();
	};
}
