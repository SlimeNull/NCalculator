#pragma once

#include "Expr.h"
#include "../Token.h"
#include <vector>
#include "exceptionhelper.h"

using namespace NCalculator;



namespace NCalculatorLibExprs
{
	//public abstract class Expr
	//{
	//    public abstract double Eval();
	//}

	class ExprSeqExpr : public Expr
	{
	public:
		const std::vector<Expr*> SeqValue;

		ExprSeqExpr(std::vector<Expr> &exprs);

		Expr *operator [](int index);

		double Eval() override;

		std::vector<Token> EnumTokens() override;
	};
}
