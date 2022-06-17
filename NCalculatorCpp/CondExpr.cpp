
#include "CondExpr.h"

CondExpr::CondExpr(Expr& condition, Expr& leftExpr, Expr& rightExpr)
{
	this->condition = condition;
	this->leftExpr = leftExpr;
	this->rightExpr = rightExpr;
}

double CondExpr::eval()
{
	return this->condition.eval() != 0 ? this->leftExpr.eval() : this->rightExpr.eval();
}
