using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// mul tail expression :
    /// 
    /// <para>| *|/|%|^ unit</para>
    /// <para>| *|/|%|^ unit mul_tail</para>
    /// </summary>
    public class MulTailExpr : BinTailExpr
    {
        public MulTailExpr(Token op, Expr right, BinTailExpr? tail) : base(op, right, tail)
        {
            if (op.Kind != TokenKind.Mul &&
                op.Kind != TokenKind.Div &&
                op.Kind != TokenKind.Mod &&
                op.Kind != TokenKind.Pow)
                throw new ArgumentException("Not a Mul/Div/Mod/Pow token");
        }

        public override double Eval(double left)
        {
            double value = Operator.Kind switch
            {
                TokenKind.Mul => left * RightExpr.Eval(),
                TokenKind.Div => left / RightExpr.Eval(),
                TokenKind.Mod => left % RightExpr.Eval(),
                TokenKind.Pow => Math.Pow(left, RightExpr.Eval()),
                _ => 0
            };

            if (TailExpr is not null)
                value = TailExpr.Eval(value);

            return value;
        }
    }
}
