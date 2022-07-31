#include "CondExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	CondExpr::CondExpr(Expr *condition, Expr *leftExpr, Expr *rightExpr) : Condition(condition), LeftExpr(leftExpr), RightExpr(rightExpr)
	{
	}

	double CondExpr::Eval()
	{
		return Condition->Eval() != 0 ? LeftExpr->Eval() : RightExpr->Eval();
	}

	std::vector<Token> CondExpr::EnumTokens()
	{
		std::vector<Token> rst = std::vector<Token>();

		auto v1 = Condition->EnumTokens();
		auto v2 = LeftExpr->EnumTokens();
		auto v3 = RightExpr->EnumTokens();

		rst.insert(rst.end(), v1.begin(), v1.end());
		rst.push_back(Token(TokenKind::Question, L""));
		rst.insert(rst.end(), v2.begin(), v2.end());
		rst.push_back(Token(TokenKind::Colon, L""));
		rst.insert(rst.end(), v3.begin(), v3.end());
	}
}
