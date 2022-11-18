#include "CondExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	cond_expr::cond_expr(expr *condition, expr *leftExpr, expr *rightExpr) : Condition(condition), LeftExpr(leftExpr), RightExpr(rightExpr)
	{
	}

	double cond_expr::eval()
	{
		return Condition->eval() != 0 ? LeftExpr->eval() : RightExpr->eval();
	}

	std::vector<token> cond_expr::enum_tokens()
	{
		std::vector<token> rst = std::vector<token>();

		auto v1 = Condition->enum_tokens();
		auto v2 = LeftExpr->enum_tokens();
		auto v3 = RightExpr->enum_tokens();

		rst.insert(rst.end(), v1.begin(), v1.end());
		rst.push_back(token(token_kind::Question, L""));
		rst.insert(rst.end(), v2.begin(), v2.end());
		rst.push_back(token(token_kind::Colon, L""));
		rst.insert(rst.end(), v3.begin(), v3.end());
	}
}
