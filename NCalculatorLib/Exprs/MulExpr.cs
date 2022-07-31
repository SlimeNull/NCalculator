using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// multiply expression
    /// 
    /// | unit * | / | % | ^ mul_expr
    /// | unit * | / | % | ^ unit
    /// </summary>
    public class MulExpr : BinExpr
    {
        public MulExpr(Token op, Expr left, Expr right) : base(op, left, right)
        { }

        public override double Eval()
        {
            return Operator.Kind switch
            {
                TokenKind.Mul => LeftExpr.Eval() * RightExpr.Eval(),
                TokenKind.Div => LeftExpr.Eval() / RightExpr.Eval(),
                TokenKind.Mod => LeftExpr.Eval() % RightExpr.Eval(),
                TokenKind.Pow => Math.Pow(LeftExpr.Eval(), RightExpr.Eval()),
                _ => throw new Exception("Invalid operator")
            };
        }
    }
}
