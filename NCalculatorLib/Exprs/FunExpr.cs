using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    /// <summary>
    /// id quote_expr
    /// </summary>
    public class FunExpr : Expr
    {
        public readonly Token Func;
        public readonly ExprSeqExpr Params;

        public FunExpr(Token func, ExprSeqExpr param)
        {
            Func = func;
            Params = param;
        }

        public override IEnumerable<Token> EnumTokens()
        {
            yield return Func;
            yield return new Token(TokenKind.LParen, null);

            foreach (Token token in Params.EnumTokens())
                yield return token;

            yield return new Token(TokenKind.RParen, null);
        }

        public override double Eval()
        {
            Func<double[], double>? func;
            if (NCalc.Functions.TryGetValue(Func.Value!, out func) ||
                NCalc.DefaultFunctions.TryGetValue(Func.Value!, out func))
                return func.Invoke(Params.SeqValue.Select(expr => expr.Eval()).ToArray());
            else
                throw new ArgumentException($"Unknown function: {Func.Value}");
        }
    }
}
