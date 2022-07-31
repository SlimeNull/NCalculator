using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    public class EqExpr : Expr
    {
        public EqExpr(Token @operator, Expr leftExpr, Expr rightExpr)
        {
            Operator = @operator;
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
                TokenKind.Eq => LeftExpr.Eval() == RightExpr.Eval() ? 1 : 0,
                TokenKind.NoEq => LeftExpr.Eval() != RightExpr.Eval() ? 1 : 0,
                _ => throw new ArgumentOutOfRangeException("Unkonwn operator"),
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
