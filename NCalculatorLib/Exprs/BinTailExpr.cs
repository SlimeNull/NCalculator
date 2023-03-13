#nullable enable

using Null.Calculator;

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// 
    /// </summary>
    public abstract class BinTailExpr : Expr
    {
        public BinTailExpr(Token op, Expr right, BinTailExpr? tail)
        {
            Operator = op;
            RightExpr = right;
            TailExpr = tail;
        }

        public Token Operator { get; }
        public Expr RightExpr { get; }
        public BinTailExpr? TailExpr { get; }

        public abstract double Eval(double left);

        public override double Eval() => throw new InvalidOperationException();

        public override IEnumerable<Token> EnumTokens()
        {
            yield return Operator;
            foreach (var token in RightExpr.EnumTokens())
                yield return token;

            if (TailExpr != null)
            {
                foreach (var token in TailExpr.EnumTokens())
                    yield return token;
            }
        }
    }
}
