#include "NumExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	NumExpr::NumExpr(const std::wstring &value) : Value(value)
	{
	}

	std::vector<Token> NumExpr::EnumTokens()
	{
		std::vector<Token> rst = std::vector<Token>();
		rst.push_back(Token(TokenKind::Number, Value));
		return  rst;
	}

	double NumExpr::Eval()
	{
		return std::stod(Value);
	}
}
