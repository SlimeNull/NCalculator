using Null.Calculator;

namespace NCalculatorLib.Exprs
{
    public abstract class BinExpr : Expr
    {
        public readonly Token Operator;
        public readonly Expr LeftExpr;
        public readonly Expr RightExpr;

        public BinExpr(Token op, Expr left, Expr right)
        {
            Operator = op;
            LeftExpr = left;
            RightExpr = right;
        }

        public static MulExpr SpinExpr(MulExpr expr)
        {
            if (expr.RightExpr is MulExpr rightExpr)
            {
                MulExpr _rightExpr = SpinExpr(rightExpr);
                return new MulExpr(_rightExpr.Operator,
                    SpinExpr(new MulExpr(expr.Operator, expr.LeftExpr, _rightExpr.LeftExpr)),
                    _rightExpr.RightExpr);
            }
            else if (expr.LeftExpr is MulExpr leftExpr)
            {
                return new MulExpr(expr.Operator, SpinExpr(leftExpr), expr.RightExpr);
            }
            else
            {
                return expr;
            }
        }

        public static PlusExpr SpinExpr(PlusExpr expr)
        {
            if (expr.RightExpr is PlusExpr rightExpr)
            {
                PlusExpr _rightExpr = SpinExpr(rightExpr);
                return new PlusExpr(_rightExpr.Operator,
                    SpinExpr(new PlusExpr(expr.Operator, expr.LeftExpr, _rightExpr.LeftExpr)),
                    _rightExpr.RightExpr);
            }
            else if (expr.LeftExpr is PlusExpr leftExpr)
            {
                return new PlusExpr(expr.Operator, SpinExpr(leftExpr), expr.RightExpr);
            }
            else
            {
                return expr;
            }
        }

        public override IEnumerable<Token> EnumTokens()
        {
            foreach (Token token in LeftExpr.EnumTokens())
                yield return token;

            yield return Operator;

            foreach (Token token in RightExpr.EnumTokens())
                yield return token;
        }
    }
}