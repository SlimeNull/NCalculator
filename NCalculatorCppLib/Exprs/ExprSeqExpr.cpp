#include "ExprSeqExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	ExprSeqExpr::ExprSeqExpr(std::vector<Expr> &exprs)
	{
		if (exprs->Length < 1)
		{
			throw ArgumentOutOfRangeException();
		}

		SeqValue = exprs;
	}

	Expr *ExprSeqExpr::operator [](int index)
	{
		return SeqValue[index];
	}

	double ExprSeqExpr::Eval()
	{
		return SeqValue[0]->Eval();
	}

	std::vector<Token> ExprSeqExpr::EnumTokens()
	{
		for (int i = 0; i < SeqValue.size() - 1; i++)
		{
			for (auto token : SeqValue[i]->EnumTokens())
			{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
				yield return token;
			}
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return Token(TokenKind::Comma, L"");
		}

		for (Token token : SeqValue.Last().EnumTokens())
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return token;
		}
	}
}
