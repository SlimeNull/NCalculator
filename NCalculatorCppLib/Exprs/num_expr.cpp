#include "NumExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	NumExpr::NumExpr(const std::wstring &value) : Value(value)
	{
	}

	std::vector<token> NumExpr::enum_tokens()
	{
		std::vector<token> rst = std::vector<token>();
		rst.push_back(token(token_kind::Number, Value));
		return  rst;
	}

	double NumExpr::eval()
	{
		return std::stod(Value);
	}
}
