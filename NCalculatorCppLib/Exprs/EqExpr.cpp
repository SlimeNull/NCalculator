#include "EqExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	EqExpr::EqExpr(Token operator_Keyword, Expr *leftExpr, Expr *rightExpr) : Operator(operator_Keyword), LeftExpr(leftExpr), RightExpr(rightExpr)
	{
	}

	double EqExpr::Eval()
	{
		int tempVar2;
		switch (Operator.Kind)
		{
			case TokenKind::Eq:
				tempVar2 = LeftExpr->Eval() == RightExpr->Eval() ? 1 : 0;
				break;
			case TokenKind::NoEq:
				tempVar2 = LeftExpr->Eval() != RightExpr->Eval() ? 1 : 0;
				break;
			default:
//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
//ORIGINAL LINE: tempVar2 = throw new ArgumentOutOfRangeException("Unkonwn operator");
				tempVar2 = throw ArgumentOutOfRangeException("Unkonwn operator");
				break;
		}
		return tempVar2;
	}

	std::vector<Token> EqExpr::EnumTokens()
	{
		for (auto token : *LeftExpr->EnumTokens())
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return token;
		}

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
		yield return Operator;

		for (auto token : *RightExpr->EnumTokens())
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return token;
		}
	}
}
