#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// add expression :
    /// 
    /// <para>| mul plus_tail</para>
    /// <para>| unit plus_tail</para>
    /// </summary>
    public class PlusExpr : BinExpr
    {
        public PlusExpr(Expr left, PlusTailExpr tail) : base(left, tail)
        {

        }
    }
}
