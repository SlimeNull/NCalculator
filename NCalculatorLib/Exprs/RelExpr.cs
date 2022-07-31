using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    public class RelExpr : Expr
    {
        public RelExpr(Token opt, Expr leftExpr, Expr rightExpr)
        {
            Operator = opt;
            LeftExpr = leftExpr;
            RightExpr = rightExpr;
        }

        public readonly Token Operator;
        public readonly Expr LeftExpr;
        public readonly Expr RightExpr;

        public override double Eval()
        {
            return Operator.Kind switch
            {
                TokenKind.Gtr => LeftExpr.Eval() > RightExpr.Eval() ? 1 : 0,
                TokenKind.Lss => LeftExpr.Eval() < RightExpr.Eval() ? 1 : 0,
                TokenKind.GtrEq => LeftExpr.Eval() >= RightExpr.Eval() ? 1 : 0,
                TokenKind.LssEq => LeftExpr.Eval() <= RightExpr.Eval() ? 1 : 0,
                _ => throw new ArgumentOutOfRangeException("Unkonw operator"),
            };
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
