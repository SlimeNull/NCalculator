#include "UnitExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	UnitExpr::UnitExpr(Expr *value, bool signed_Keyword) : Signed(signed_Keyword), Value(value)
	{
	}

	std::vector<Token> UnitExpr::EnumTokens()
	{
		if (Signed)
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return Token(TokenKind::Sub, L"");
		}

		for (auto token : *Value->EnumTokens())
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return token;
		}
	}

	double UnitExpr::Eval()
	{
		return Signed ? -Value->Eval() : Value->Eval();
	}
}
