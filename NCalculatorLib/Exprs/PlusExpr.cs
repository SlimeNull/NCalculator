using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// add expression
    /// 
    /// | mul + | - plus
    /// | mul + | - mul
    /// | unit + | - plus
    /// | unit + | - mul
    /// | unit - | - unit
    /// </summary>
    public class PlusExpr : BinExpr
    {
        public PlusExpr(Token op, Expr left, Expr right) : base(op, left, right)
        { }

        public override double Eval()
        {
            return Operator.Kind switch
            {
                TokenKind.Plus => LeftExpr.Eval() + RightExpr.Eval(),
                TokenKind.Sub => LeftExpr.Eval() - RightExpr.Eval(),
                _ => throw new Exception("Invalid operator")
            };
        }
    }
}
