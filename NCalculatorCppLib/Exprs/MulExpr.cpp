﻿#include "MulExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	MulExpr::MulExpr(Token op, Expr *left, Expr *right) : BinExpr(op, left, right)
	{
	}

	double MulExpr::Eval()
	{
	//C# TO C++ CONVERTER TODO TASK: The following 'switch expression' was not converted by C# to C++ Converter:
	//			return Operator.Kind switch
	//			{
	//				TokenKind.Mul => LeftExpr.Eval() * RightExpr.Eval(),
	//				TokenKind.Div => LeftExpr.Eval() / RightExpr.Eval(),
	//				TokenKind.Mod => LeftExpr.Eval() % RightExpr.Eval(),
	//				TokenKind.Pow => Math.Pow(LeftExpr.Eval(), RightExpr.Eval()),
	//				_ => throw new Exception("Invalid operator")
	//			};
	}
}
