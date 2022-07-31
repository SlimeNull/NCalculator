using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// basic number
    /// 
    /// | num_literal
    /// </summary>
    public class NumExpr : Expr
    {
        public readonly string Value;

        public NumExpr(string value)
        {
            Value = value;
        }

        public override IEnumerable<Token> EnumTokens()
        {
            yield return new Token(TokenKind.Number, Value);
        }

        public override double Eval()
        {
            return double.Parse(Value);
        }
    }
}
