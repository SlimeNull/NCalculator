#include "BinExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	BinExpr::BinExpr(Token op, Expr *left, Expr *right) : Operator(op), LeftExpr(left), RightExpr(right)
	{
	}

	MulExpr *BinExpr::SpinExpr(MulExpr *expr)
	{
		MulExpr *rightExpr = dynamic_cast<MulExpr*>(expr->RightExpr);
		if (rightExpr != nullptr)
		{
			MulExpr *_rightExpr = SpinExpr(rightExpr);
			MulExpr tempVar(expr->Operator, expr->LeftExpr, _rightExpr->LeftExpr);
			return new MulExpr(_rightExpr->Operator, SpinExpr(&tempVar), _rightExpr->RightExpr);
		}
		else
		{
			MulExpr *leftExpr = dynamic_cast<MulExpr*>(expr->LeftExpr);
			if (leftExpr != nullptr)
			{
				return new MulExpr(expr->Operator, SpinExpr(leftExpr), expr->RightExpr);
			}
			else
			{
				return expr;
			}
		}
	}

	PlusExpr *BinExpr::SpinExpr(PlusExpr *expr)
	{
		PlusExpr *rightExpr = dynamic_cast<PlusExpr*>(expr->RightExpr);
		if (rightExpr != nullptr)
		{
			PlusExpr *_rightExpr = SpinExpr(rightExpr);
			PlusExpr tempVar(expr->Operator, expr->LeftExpr, _rightExpr->LeftExpr);
			return new PlusExpr(_rightExpr->Operator, SpinExpr(&tempVar), _rightExpr->RightExpr);
		}
		else
		{
			PlusExpr *leftExpr = dynamic_cast<PlusExpr*>(expr->LeftExpr);
			if (leftExpr != nullptr)
			{
				return new PlusExpr(expr->Operator, SpinExpr(leftExpr), expr->RightExpr);
			}
			else
			{
				return expr;
			}
		}
	}

	std::vector<Token> BinExpr::EnumTokens()
	{
		std::vector<Token> rst = std::vector<Token>();
		auto v1 = LeftExpr->EnumTokens();
		auto v2 = RightExpr->EnumTokens();

		rst.insert(rst.end(), v1.begin(), v1.end());
		rst.push_back(Operator);
		rst.insert(rst.end(), v2.begin(), v2.end());

		return rst;
	}
}
