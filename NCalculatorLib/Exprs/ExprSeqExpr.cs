using Null.Calculator;

#nullable enable

namespace NCalculatorLib.Exprs
{
    //public abstract class Expr
    //{
    //    public abstract double Eval();
    //}

    public class ExprSeqExpr : Expr
    {
        public readonly Expr[] SeqValue;

        public ExprSeqExpr(params Expr[] exprs)
        {
            if (exprs.Length < 1)
                throw new ArgumentOutOfRangeException();

            SeqValue = exprs;
        }

        public Expr this[int index] => SeqValue[index];

        public override double Eval()
        {
            return SeqValue[0].Eval();
        }

        public override IEnumerable<Token> EnumTokens()
        {
            for (int i = 0; i < SeqValue.Length - 1; i++)
            {
                foreach (Token token in SeqValue[i].EnumTokens())
                    yield return token;
                yield return new Token(TokenKind.Comma, null);
            }

            foreach (Token token in SeqValue.Last().EnumTokens())
                yield return token;
        }
    }
}
