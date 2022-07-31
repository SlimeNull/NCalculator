using System;
using System.Collections.Generic;
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

        public bool MatchExprSeqExpr(ref int index, out ExprSeqExpr? rst)
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

        public bool MatchExpr(ref int index, out Expr? rst)
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

        public bool MatchMathExpr(ref int index, out Expr? rst)
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

        public bool MatchLogicExpr(ref int index, out Expr? rst)
        {
            if (MatchCondExpr(ref index, out var condExpr))
            {
                rst = condExpr;
                return true;
            }
            else if (MatchEqExpr(ref index, out var eqExpr))
            {
                rst = eqExpr;
                return true;
            }
            else if (MatchRelExpr(ref index, out var relExpr))
            {
                rst = relExpr;
                return true;
            }

            rst = null;
            return false;
        }

        public bool MatchCondExpr(ref int index, out CondExpr? rst)
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

        public bool MatchEqExpr(ref int index, out EqExpr? rst)
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

        public bool MatchRelExpr(ref int index, out RelExpr? rst)
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

        public bool MatchQuoteExpr(ref int index, out Expr? rst)
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

        public bool MatchPlusExpr(ref int index, out PlusExpr? rst)
        {
            rst = null;
            int tempindex1 = index;
            if (MatchMulExpr(ref tempindex1, out var mulExpr))
            {
                if (tempindex1 >= Tokens.Length)
                    return false;

                var optToken = Tokens[tempindex1];
                if (optToken.Kind != TokenKind.Plus &&
                    optToken.Kind != TokenKind.Sub)
                    return false;

                int tempindex2 = tempindex1 + 1;
                if (MatchPlusExpr(ref tempindex2, out var plusExpr))
                {
                    rst = new PlusExpr(optToken, mulExpr!, plusExpr!);
                    index = tempindex2;
                    return true;
                }
                else if (MatchMulExpr(ref tempindex2, out var mulExpr2))
                {
                    rst = new PlusExpr(optToken, mulExpr!, mulExpr2!);
                    index = tempindex2;
                    return true;
                }
            }
            else if (MatchUnitExpr(ref tempindex1, out var unitExpr))
            {
                if (tempindex1 >= Tokens.Length)
                    return false;

                Token optToken = Tokens[tempindex1];
                if (optToken.Kind != TokenKind.Plus &&
                    optToken.Kind != TokenKind.Sub)
                    return false;

                int tempindex2 = tempindex1 + 1;
                if (MatchPlusExpr(ref tempindex2, out var plusExpr))
                {
                    rst = new PlusExpr(plusExpr!.Operator,
                        new PlusExpr(optToken, unitExpr!, plusExpr!.LeftExpr)!,
                        plusExpr.RightExpr!);
                    rst = BinExpr.SpinExpr(rst);

                    index = tempindex2;
                    return true;
                }
                else if (MatchMulExpr(ref tempindex2, out var mulExpr2))
                {
                    rst = new PlusExpr(optToken, unitExpr!, mulExpr2!);
                    index = tempindex2;
                    return true;
                }
                else if (MatchUnitExpr(ref tempindex2, out var unitExpr2))
                {
                    rst = new PlusExpr(optToken, unitExpr!, unitExpr2!);
                    index = tempindex2;
                    return true;
                }
            }

            return false;
        }

        public bool MatchMulExpr(ref int index, out MulExpr? rst)
        {
            rst = null;
            int tempindex1 = index;

            // 匹配左侧是否是计算单元
            if (MatchUnitExpr(ref tempindex1, out var unitExpr))
            {
                if (tempindex1 >= Tokens.Length)
                    return false;

                // 匹配是否是乘法符号 * / ^
                Token optToken = Tokens[tempindex1];
                if (optToken.Kind != TokenKind.Mul &&
                    optToken.Kind != TokenKind.Div &&
                    optToken.Kind != TokenKind.Pow &&
                    optToken.Kind != TokenKind.Mod)
                    return false;

                int tempindex2 = tempindex1 + 1;
                if (MatchMulExpr(ref tempindex2, out var mulExpr))
                {
                    rst = new MulExpr(mulExpr!.Operator,
                              new MulExpr(optToken, unitExpr!, mulExpr!.LeftExpr),
                              mulExpr.RightExpr!);
                    rst = BinExpr.SpinExpr(rst);

                    index = tempindex2;
                    return true;
                }
                else if (MatchUnitExpr(ref tempindex2, out var unitExpr2))
                {
                    rst = new MulExpr(optToken, unitExpr!, unitExpr2!);
                    index = tempindex2;
                    return true;
                }
            }

            return false;
        }

        public bool MatchUnitExpr(ref int index, out UnitExpr? rst)
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

        public bool MatchNumExpr(ref int index, out NumExpr? rst)
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
