using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using NCalculatorLib.Exprs;
using Null.Calculator;

#nullable enable

namespace NCalculatorLib
{
    public class Parser
    {
        public Token[] Tokens { get; }


        public Parser(Token[] tokens)
        {
            Tokens = tokens;
        }

        public bool MatchExprSeqExpr(ref int index, [NotNullWhen(true)] out ExprSeqExpr? rst)
        {
            rst = null;
            int tempindex1 = index;
            if (MatchExpr(ref tempindex1, out var firstExpr))
            {
                List<Expr> exprs = new List<Expr>() { firstExpr! };

                while (tempindex1 < Tokens.Length)
                {
                    if (Tokens[tempindex1].Kind != TokenKind.Comma)
                    {
                        index = tempindex1;
                        rst = new ExprSeqExpr(exprs.ToArray());
                        return true;
                    }

                    tempindex1 += 1;
                    if (!MatchExpr(ref tempindex1, out var nextExpr))
                        return false;

                    exprs.Add(nextExpr!);
                }
            }

            return false;
        }

        public bool MatchExpr(ref int index, [NotNullWhen(true)] out Expr? rst)
        {
            if (MatchLogicExpr(ref index, out var logicExpr))
            {
                rst = logicExpr;
                return true;
            }
            if (MatchMathExpr(ref index, out var mathExpr))
            {
                rst = mathExpr;
                return true;
            }

            rst = null;
            return false;
        }

        public bool MatchMathExpr(ref int index, [NotNullWhen(true)] out Expr? rst)
        {
            if (MatchPlusExpr(ref index, out var plusExpr))
            {
                rst = plusExpr;
                return true;
            }

            if (MatchMulExpr(ref index, out var mulExpr))
            {
                rst = mulExpr;
                return true;
            }

            if (MatchFunExpr(ref index, out var funExpr))
            {
                rst = funExpr;
                return true;
            }

            if (MatchQuoteExpr(ref index, out var quotedExpr))
            {
                rst = quotedExpr;
                return true;
            }

            if (MatchUnitExpr(ref index, out var unitExpr))
            {
                rst = unitExpr;
                return true;
            }

            rst = null;
            return false;
        }

        public bool MatchLogicExpr(ref int index, [NotNullWhen(true)] out Expr? rst)
        {
            rst = null;

            int tmpindex = index;
            if (MatchCondExpr(ref tmpindex, out var condExpr))
                rst = condExpr;
            else if (MatchEqExpr(ref tmpindex, out var eqExpr))
                rst = eqExpr;
            else if (MatchRelExpr(ref tmpindex, out var relExpr))
                rst = relExpr;
            else
                return false;

            index = tmpindex;
            return true;
        }

        public bool MatchCondExpr(ref int index, [NotNullWhen(true)] out CondExpr? rst)
        {
            rst = null;
            int tempindex1 = index;
            if (MatchEqExpr(ref tempindex1, out var eqExpr))
            {
                if (tempindex1 < Tokens.Length && Tokens[tempindex1].Kind != TokenKind.Question)
                    return false;

                int tempindex2 = tempindex1 + 1;
                if (MatchCondExpr(ref tempindex2, out var condExpr))
                {
                    if (Tokens[tempindex2].Kind != TokenKind.Colon)
                        return false;

                    int tempindex3 = tempindex2 + 1;
                    if (MatchCondExpr(ref tempindex3, out var condExpr2))
                    {
                        rst = new CondExpr(eqExpr!, condExpr!, condExpr2!);
                        index = tempindex3;
                        return true;
                    }
                    else if (MatchMathExpr(ref tempindex2, out var mathExpr))
                    {
                        rst = new CondExpr(eqExpr!, condExpr!, mathExpr!);
                        index = tempindex3;
                        return true;
                    }
                }
                else if (MatchMathExpr(ref tempindex2, out var mathExpr2))
                {
                    if (Tokens[tempindex2].Kind != TokenKind.Colon)
                        return false;

                    int tempindex3 = tempindex2 + 1;
                    if (MatchMathExpr(ref tempindex3, out var mathExpr3))
                    {
                        rst = new CondExpr(eqExpr!, mathExpr2!, mathExpr3!);
                        index = tempindex3;
                        return true;
                    }
                }
            }
            else if (MatchRelExpr(ref tempindex1, out var relExpr))
            {
                if (tempindex1 < Tokens.Length && Tokens[tempindex1].Kind != TokenKind.Question)
                    return false;

                int tempindex2 = tempindex1 + 1;

                if (MatchCondExpr(ref tempindex2, out var condExpr))
                {
                    if (Tokens[tempindex2].Kind != TokenKind.Colon)
                        return false;

                    int tempindex3 = tempindex2 + 1;
                    if (MatchCondExpr(ref tempindex3, out var condExpr2))
                    {
                        rst = new CondExpr(relExpr!, condExpr!, condExpr2!);
                        index = tempindex3;
                        return true;
                    }
                    else if (MatchMathExpr(ref tempindex2, out var mathExpr))
                    {
                        rst = new CondExpr(relExpr!, condExpr!, mathExpr!);
                        index = tempindex3;
                        return true;
                    }
                }
                else if (MatchMathExpr(ref tempindex2, out var mathExpr2))
                {
                    if (Tokens[tempindex2].Kind != TokenKind.Colon)
                        return false;

                    int tempindex3 = tempindex2 + 1;
                    if (MatchMathExpr(ref tempindex3, out var mathExpr3))
                    {
                        rst = new CondExpr(relExpr!, mathExpr2!, mathExpr3!);
                        index = tempindex3;
                        return true;
                    }
                }
            }

            return false;
        }

        public bool MatchEqExpr(ref int index, [NotNullWhen(true)] out EqExpr? rst)
        {
            rst = null;
            int tempindex1 = index;
            if (MatchMathExpr(ref tempindex1, out var mathExpr))
            {
                if (tempindex1 >= Tokens.Length)
                    return false;

                var optToken = Tokens[tempindex1];
                if (optToken.Kind != TokenKind.Eq &&
                    optToken.Kind != TokenKind.NoEq)
                    return false;

                int tempindex2 = tempindex1 + 1;
                if (MatchEqExpr(ref tempindex2, out var relExpr2))
                {
                    rst = new EqExpr(optToken, mathExpr!, relExpr2!);
                    index = tempindex2;
                    return true;
                }
                else if (MatchMathExpr(ref tempindex2, out var mathExpr2))
                {
                    rst = new EqExpr(optToken, mathExpr!, mathExpr2!);
                    index = tempindex2;
                    return true;
                }
            }

            return false;
        }

        public bool MatchRelExpr(ref int index, [NotNullWhen(true)] out RelExpr? rst)
        {
            rst = null;
            int tempindex1 = index;
            if (MatchMathExpr(ref tempindex1, out var mathExpr))
            {
                if (tempindex1 >= Tokens.Length)
                    return false;

                var optToken = Tokens[tempindex1];
                if (optToken.Kind != TokenKind.Gtr &&
                    optToken.Kind != TokenKind.GtrEq &&
                    optToken.Kind != TokenKind.Lss &&
                    optToken.Kind != TokenKind.LssEq)
                    return false;

                int tempindex2 = tempindex1 + 1;
                if (MatchRelExpr(ref tempindex2, out var relExpr2))
                {
                    rst = new RelExpr(optToken, mathExpr!, relExpr2!);
                    index = tempindex2;
                    return true;
                }
                else if (MatchMathExpr(ref tempindex2, out var mathExpr2))
                {
                    rst = new RelExpr(optToken, mathExpr!, mathExpr2!);
                    index = tempindex2;
                    return true;
                }
            }

            return false;
        }

        public bool MatchFunExpr(ref int index, out FunExpr? rst)
        {
            rst = null;
            if (index >= Tokens.Length)
                return false;

            if (Tokens[index].Kind != TokenKind.Identifier)
                return false;

            int tempindex = index + 1;
            if (MatchQuoteExprSeqExpr(ref tempindex, out var expr))
            {
                rst = new FunExpr(Tokens[index], expr!);
                index = tempindex;
                return true;
            }

            return false;
        }

        public bool MatchQuoteExprSeqExpr(ref int index, out ExprSeqExpr? rst)
        {
            rst = null;
            if (index >= Tokens.Length)
                return false;

            if (Tokens[index].Kind != TokenKind.LParen)
                return false;

            int tempindex = index + 1;
            if (MatchExprSeqExpr(ref tempindex, out var expr))
            {
                if (tempindex >= Tokens.Length)
                    return false;

                if (Tokens[tempindex].Kind == TokenKind.RParen)
                {
                    rst = expr;
                    index = tempindex + 1;
                    return true;
                }
            }

            return false;
        }

        public bool MatchQuoteExpr(ref int index, [NotNullWhen(true)] out Expr? rst)
        {
            rst = null;
            if (index >= Tokens.Length)
                return false;

            if (Tokens[index].Kind != TokenKind.LParen)
                return false;

            int tempindex = index + 1;
            if (MatchExpr(ref tempindex, out var expr))
            {
                if (tempindex >= Tokens.Length)
                    return false;

                if (Tokens[tempindex].Kind == TokenKind.RParen)
                {
                    rst = expr;
                    index = tempindex + 1;
                    return true;
                }
            }

            return false;
        }

        public bool MatchPlusExpr(ref int index, [NotNullWhen(true)] out PlusExpr? rst)
        {
            rst = null;
            int tmpindex = index;

            Expr? left;
            if (MatchMulExpr(ref tmpindex, out var mulExpr))
                left = mulExpr;
            else if (MatchUnitExpr(ref tmpindex, out var unitExpr))
                left = unitExpr;
            else
                return false;

            if (MatchPlusTailExpr(ref tmpindex, out PlusTailExpr? tailExpr))
            {
                index = tmpindex;
                rst = new PlusExpr(left, tailExpr);
                return true;
            }

            return false;
        }

        public bool MatchPlusTailExpr(ref int index, [NotNullWhen(true)] out PlusTailExpr? rst)
        {
            rst = null;
            int tmpindex = index;
            if (tmpindex >= Tokens.Length)
                return false;

            Token optToken = Tokens[tmpindex];
            if (optToken.Kind != TokenKind.Plus &&
                optToken.Kind != TokenKind.Sub)
                return false;

            tmpindex++;

            Expr? rightExpr;
            if (MatchMulExpr(ref tmpindex, out MulExpr? mulExpr))
                rightExpr = mulExpr;
            else if (MatchUnitExpr(ref tmpindex, out UnitExpr? unitExpr))
                rightExpr = unitExpr;
            else
                return false;

            MatchPlusTailExpr(ref tmpindex, out PlusTailExpr? tailExpr);

            index = tmpindex;
            rst = new PlusTailExpr(optToken, rightExpr, tailExpr);
            return true;
        }

        public bool MatchMulExpr(ref int index, [NotNullWhen(true)] out MulExpr? rst)
        {
            int tmpindex = index;
            if (MatchUnitExpr(ref tmpindex, out UnitExpr? unitExpr) &&
                MatchMulTailExpr(ref tmpindex, out MulTailExpr? tailExpr))
            {
                index = tmpindex;
                rst = new MulExpr(unitExpr, tailExpr);
                return true;
            }

            rst = null;
            return false;
        }

        public bool MatchMulTailExpr(ref int index, [NotNullWhen(true)] out MulTailExpr? rst)
        {
            rst = null;
            int tmpindex = index;

            if (tmpindex >= Tokens.Length)
                return false;

            Token optToken = Tokens[tmpindex];
            if (optToken.Kind != TokenKind.Mul &&
                optToken.Kind != TokenKind.Div &&
                optToken.Kind != TokenKind.Mod &&
                optToken.Kind != TokenKind.Pow)
                return false;

            tmpindex++;
            if (!MatchUnitExpr(ref tmpindex, out UnitExpr? unitExpr))
                return false;

            MatchMulTailExpr(ref tmpindex, out MulTailExpr? tailExpr);

            index = tmpindex;
            rst = new MulTailExpr(optToken, unitExpr, tailExpr);
            return true;
        }

        public bool MatchUnitExpr(ref int index, [NotNullWhen(true)] out UnitExpr? rst)
        {
            rst = null;
            bool signed;
            int tempindex = index;

            if (index >= Tokens.Length)
                return false;

            signed = Tokens[index].Kind == TokenKind.Sub;
            if (signed)
                tempindex++;

            if (MatchNumExpr(ref tempindex, out var numExpr))
            {
                rst = new UnitExpr(numExpr!, signed);
                index = tempindex;
                return true;
            }
            else if (MatchFunExpr(ref tempindex, out var funExpr))
            {
                rst = new UnitExpr(funExpr!, signed);
                index = tempindex;
                return true;
            }
            else if (MatchConstExpr(ref tempindex, out var constExpr))
            {
                rst = new UnitExpr(constExpr!, signed);
                index = tempindex;
                return true;
            }
            else if (MatchQuoteExpr(ref tempindex, out var quoteExpr))
            {
                rst = new UnitExpr(quoteExpr!, signed);
                index = tempindex;
                return true;
            }

            return false;
        }

        public bool MatchNumExpr(ref int index, [NotNullWhen(true)] out NumExpr? rst)
        {
            rst = null;
            if (index >= Tokens.Length)
                return false;

            if (Tokens[index].Kind == TokenKind.Number)
            {
                rst = new NumExpr(Tokens[index].Value!);
                index += 1;
                return true;
            }

            return false;
        }

        public bool MatchConstExpr(ref int index, out ConstExpr? rst)
        {
            rst = null;
            if (index >= Tokens.Length)
                return false;

            if (Tokens[index].Kind == TokenKind.Identifier)
            {
                rst = new ConstExpr(Tokens[index].Value!);
                index += 1;
                return true;
            }

            return false;
        }

        public Expr Parse()
        {
            int index = 0;
            if (MatchExpr(ref index, out var rst))
            {
                if (index < Tokens.Length)
                    throw new ArgumentException($"Unexpected token: {Tokens[index]} at index {index}");
                return rst!;
            }
            else
            {
                throw new ArgumentException();
            }
        }
    }
}
