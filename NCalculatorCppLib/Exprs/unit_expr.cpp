#include "UnitExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	UnitExpr::UnitExpr(expr *value, bool signed_Keyword) : Signed(signed_Keyword), Value(value)
	{
	}

	std::vector<token> UnitExpr::enum_tokens()
	{
		std::vector<token> vec = std::vector<token>();
		if (Signed)
		{
			vec.push_back(token(token_kind::Sub, L""));
		}

		for (auto token : Value->enum_tokens())
		{
			vec.push_back(token);
		}

		return vec;
	}

	double UnitExpr::eval()
	{
		return Signed ? -Value->eval() : Value->eval();
	}
}
