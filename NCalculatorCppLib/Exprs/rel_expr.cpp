#include "RelExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	RelExpr::RelExpr(Token opt, Expr *leftExpr, Expr *rightExpr) : Operator(opt), LeftExpr(leftExpr), RightExpr(rightExpr)
	{
	}

	double RelExpr::Eval()
	{
		int tempVar5;
		switch (Operator.Kind)
		{
			case TokenKind::Gtr:
				tempVar5 = LeftExpr->Eval() > RightExpr->Eval() ? 1 : 0;
				break;
			case TokenKind::Lss:
				tempVar5 = LeftExpr->Eval() < RightExpr->Eval() ? 1 : 0;
				break;
			case TokenKind::GtrEq:
				tempVar5 = LeftExpr->Eval() >= RightExpr->Eval() ? 1 : 0;
				break;
			case TokenKind::LssEq:
				tempVar5 = LeftExpr->Eval() <= RightExpr->Eval() ? 1 : 0;
				break;
			default:
//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
//ORIGINAL LINE: tempVar5 = throw new ArgumentOutOfRangeException("Unkonw operator");
				tempVar5 = throw ArgumentOutOfRangeException("Unkonw operator");
				break;
		}
		return tempVar5;
	}

	std::vector<Token> RelExpr::EnumTokens()
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
