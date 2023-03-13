#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// multiply expression :
    /// 
    /// <para>| unit mul_tail</para>
    /// </summary>
    public class MulExpr : BinExpr
    {
        public MulExpr(Expr left, MulTailExpr right) : base(left, right)
        {

        }
    }
}
