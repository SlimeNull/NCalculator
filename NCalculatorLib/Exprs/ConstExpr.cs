using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    public class ConstExpr : Expr
    {
        public readonly string Name;
        public ConstExpr(string name)
        {
            Name = name;
        }

        public static double GetConst(string name)
        {
            double value;
            Func<double>? valueGetter;

            if (NCalc.Constants.TryGetValue(name, out value) ||
                NCalc.DefaultConstants.TryGetValue(name, out value))
                return value;
            else if (NCalc.Variables.TryGetValue(name, out valueGetter) ||
                     NCalc.DefaultVariables.TryGetValue(name, out valueGetter))
                return valueGetter.Invoke();
            else
                throw new ArgumentException($"Unknown constant or variable: {name}");
        }

        public override IEnumerable<Token> EnumTokens()
        {
            yield return new Token(TokenKind.Identifier, Name);
        }

        public override double Eval()
        {
            return GetConst(Name);
        }
    }
}
