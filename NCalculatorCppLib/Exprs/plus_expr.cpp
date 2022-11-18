#include "PlusExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	PlusExpr::PlusExpr(Token op, Expr *left, Expr *right) : BinExpr(op, left, right)
	{
	}

	double PlusExpr::Eval()
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
