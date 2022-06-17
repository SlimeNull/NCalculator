
#include "Expr.h"
class CondExpr :
    public Expr
{
public:
    Expr& condition;
    Expr& leftExpr;
    Expr& rightExpr;

    CondExpr(Expr& condition, Expr& leftExpr, Expr& rightExpr);

    double eval();
};
