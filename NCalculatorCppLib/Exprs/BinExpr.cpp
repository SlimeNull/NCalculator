#include "BinExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	bin_expr::bin_expr(token op, expr *left, expr *right) : Operator(op), LeftExpr(left), RightExpr(right)
	{
	}

	mul_expr *bin_expr::SpinExpr(mul_expr *expr)
	{
		mul_expr *rightExpr = dynamic_cast<mul_expr*>(expr->RightExpr);
		if (rightExpr != nullptr)
		{
			mul_expr *_rightExpr = SpinExpr(rightExpr);
			mul_expr tempVar(expr->Operator, expr->LeftExpr, _rightExpr->LeftExpr);
			return new mul_expr(_rightExpr->Operator, SpinExpr(&tempVar), _rightExpr->RightExpr);
		}
		else
		{
			mul_expr *leftExpr = dynamic_cast<mul_expr*>(expr->LeftExpr);
			if (leftExpr != nullptr)
			{
				return new mul_expr(expr->Operator, SpinExpr(leftExpr), expr->RightExpr);
			}
			else
			{
				return expr;
			}
		}
	}

	PlusExpr *bin_expr::SpinExpr(PlusExpr *expr)
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

	std::vector<token> bin_expr::enum_tokens()
	{
		std::vector<token> rst = std::vector<token>();
		auto v1 = LeftExpr->enum_tokens();
		auto v2 = RightExpr->enum_tokens();

		rst.insert(rst.end(), v1.begin(), v1.end());
		rst.push_back(Operator);
		rst.insert(rst.end(), v2.begin(), v2.end());

		return rst;
	}
}
