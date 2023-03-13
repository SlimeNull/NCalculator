using Null.Calculator;

namespace NCalculatorLib.Exprs
{
    public abstract class BinExpr : Expr
    {
        public readonly Expr LeftExpr;
        public readonly BinTailExpr TailExpr;

        public BinExpr(Expr left, BinTailExpr tail)
        {
            LeftExpr = left;
            TailExpr = tail;
        }

        public override double Eval() => TailExpr.Eval(LeftExpr.Eval());

        public override IEnumerable<Token> EnumTokens()
        {
            foreach (Token token in LeftExpr.EnumTokens())
                yield return token;

            foreach (Token token in TailExpr.EnumTokens())
                yield return token;
        }
    }
}