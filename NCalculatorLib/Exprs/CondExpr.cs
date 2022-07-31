using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    public class CondExpr : Expr
    {
        public CondExpr(Expr condition, Expr leftExpr, Expr rightExpr)
        {
            Condition = condition;
            LeftExpr = leftExpr;
            RightExpr = rightExpr;
        }

        public readonly Expr Condition;
        public readonly Expr LeftExpr;
        public readonly Expr RightExpr;

        public override double Eval()
        {
            return Condition.Eval() != 0 ? LeftExpr.Eval() : RightExpr.Eval();
        }

        public override IEnumerable<Token> EnumTokens()
        {
            foreach (Token token in Condition.EnumTokens())
                yield return token;

            yield return new Token(TokenKind.Question, null);

            foreach (Token token in LeftExpr.EnumTokens())
                yield return token;

            yield return new Token(TokenKind.Colon, null);

            foreach (Token token in LeftExpr.EnumTokens())
                yield return token;
        }
    }
}
