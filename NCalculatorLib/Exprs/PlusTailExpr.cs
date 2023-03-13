using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// plus tail expression :
    /// 
    /// <para>| +|- mul </para>
    /// <para>| +|- unit </para>
    /// <para>| +|- mul plus_tail</para>
    /// <para>| +|- unit plus_tail</para>
    /// </summary>
    public class PlusTailExpr : BinTailExpr
    {
        public PlusTailExpr(Token op, Expr right, PlusTailExpr? tail) : base(op, right, tail)
        {
            if (op.Kind != TokenKind.Plus && op.Kind != TokenKind.Sub)
                throw new ArgumentException("Not a Plus/Sub token");
        }

        public override double Eval(double left)
        {
            double value = RightExpr.Eval();

            if (Operator.Kind == TokenKind.Sub)
                value = -value;

            value += left;

            if (TailExpr is not null)
                value = TailExpr.Eval(value);

            return value;
        }
    }
}
