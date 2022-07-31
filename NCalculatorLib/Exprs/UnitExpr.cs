using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// basic unit
    /// 
    /// | num
    /// | fun_expr
    /// | quote_expr
    /// </summary>
    public class UnitExpr : Expr
    {
        public readonly bool Signed;
        public readonly Expr Value;

        public UnitExpr(Expr value, bool signed)
        {
            Value = value;
            Signed = signed;
        }

        public override IEnumerable<Token> EnumTokens()
        {
            if (Signed)
                yield return new Token(TokenKind.Sub, null);

            foreach (Token token in Value.EnumTokens())
                yield return token;
        }

        public override double Eval()
        {
            return Signed ? -Value.Eval() : Value.Eval();
        }
    }
}
