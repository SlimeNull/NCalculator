#include "ExprSeqExpr.h"

ExprSeqExpr::ExprSeqExpr(std::vector<Expr>& exprs)
{
	SeqValue = exprs;
}

double ExprSeqExpr::eval()
{
	return SeqValue[0].eval();
}

Expr& ExprSeqExpr::operator[](int index)
{
	return SeqValue[index];
}