#include "EqExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	eq_expr::eq_expr(token operator_Keyword, expr *leftExpr, expr *rightExpr) : Operator(operator_Keyword), LeftExpr(leftExpr), RightExpr(rightExpr)
	{
	}

	double eq_expr::eval()
	{
		int tempVar2;
		switch (Operator.Kind)
		{
			case token_kind::Eq:
				tempVar2 = LeftExpr->eval() == RightExpr->eval() ? 1 : 0;
				break;
			case token_kind::NoEq:
				tempVar2 = LeftExpr->eval() != RightExpr->eval() ? 1 : 0;
				break;
			default:
//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
//ORIGINAL LINE: tempVar2 = throw new ArgumentOutOfRangeException("Unkonwn operator");
				tempVar2 = throw ArgumentOutOfRangeException("Unkonwn operator");
				break;
		}
		return tempVar2;
	}

	std::vector<token> eq_expr::enum_tokens()
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
