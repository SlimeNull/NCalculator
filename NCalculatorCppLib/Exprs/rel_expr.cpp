#include "RelExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	RelExpr::RelExpr(token opt, expr *leftExpr, expr *rightExpr) : Operator(opt), LeftExpr(leftExpr), RightExpr(rightExpr)
	{
	}

	double RelExpr::eval()
	{
		int tempVar5;
		switch (Operator.Kind)
		{
			case token_kind::Gtr:
				tempVar5 = LeftExpr->eval() > RightExpr->eval() ? 1 : 0;
				break;
			case token_kind::Lss:
				tempVar5 = LeftExpr->eval() < RightExpr->eval() ? 1 : 0;
				break;
			case token_kind::GtrEq:
				tempVar5 = LeftExpr->eval() >= RightExpr->eval() ? 1 : 0;
				break;
			case token_kind::LssEq:
				tempVar5 = LeftExpr->eval() <= RightExpr->eval() ? 1 : 0;
				break;
			default:
//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
//ORIGINAL LINE: tempVar5 = throw new ArgumentOutOfRangeException("Unkonw operator");
				tempVar5 = throw ArgumentOutOfRangeException("Unkonw operator");
				break;
		}
		return tempVar5;
	}

	std::vector<token> RelExpr::enum_tokens()
	{
		for (auto token : *LeftExpr->enum_tokens())
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return token;
		}

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
		yield return Operator;

		for (auto token : *RightExpr->enum_tokens())
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return token;
		}
	}
}
