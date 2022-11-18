#include "PlusExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	PlusExpr::PlusExpr(token op, expr *left, expr *right) : bin_expr(op, left, right)
	{
	}

	double PlusExpr::eval()
	{
	//C# TO C++ CONVERTER TODO TASK: The following 'switch expression' was not converted by C# to C++ Converter:
	//			return Operator.Kind switch
	//			{
	//				TokenKind.Plus => LeftExpr.Eval() + RightExpr.Eval(),
	//				TokenKind.Sub => LeftExpr.Eval() - RightExpr.Eval(),
	//				_ => throw new Exception("Invalid operator")
	//			};
	}
}
