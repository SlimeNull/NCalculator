#nullable enable

using NCalculatorLib;
using Null.Calculator;

namespace NCalculatorLib.Exprs
{
    public abstract class Expr
    {
        public abstract double Eval();
        public abstract IEnumerable<Token> EnumTokens();

        public override string ToString()
        {
            return string.Join(' ', EnumTokens());
        }
    }
}
