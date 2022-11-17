#include "Parser.h"
#include "Exprs/BinExpr.h"

using namespace NCalculatorLibExprs;
using namespace NCalculator;

namespace NCalculatorLib
{

    std::vector<token> Parser::getTokens() const
    {
        return Tokens;
    }

    Parser::Parser(std::vector<token>& tokens)
    {
        Tokens = tokens;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchExprSeqExpr(ref int index, out ExprSeqExpr? rst)
    bool Parser::MatchExprSeqExpr(int& index, expr_seq_expr*& rst)
    {
        rst = nullptr;
        int tempindex1 = index;
        NCalculatorLibExprs::expr* firstExpr;
        if (MatchExpr(tempindex1, firstExpr))
        {
            std::vector<expr*> exprs = { firstExpr };

            while (tempindex1 < getTokens().size())
            {
                if (getTokens()[tempindex1].Kind != token_kind::Comma)
                {
                    index = tempindex1;
                    rst = new expr_seq_expr(exprs);
                    return true;
                }

                tempindex1 += 1;
                NCalculatorLibExprs::expr* nextExpr;
                if (!MatchExpr(tempindex1, nextExpr))
                {
                    return false;
                }

                exprs.push_back(nextExpr);
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchExpr(ref int index, out Expr? rst)
    bool Parser::MatchExpr(int& index, expr*& rst)
    {
        NCalculatorLibExprs::expr* logicExpr;
        if (MatchLogicExpr(index, logicExpr))
        {
            rst = logicExpr;
            return true;
        }
        NCalculatorLibExprs::expr* mathExpr;
        if (MatchMathExpr(index, mathExpr))
        {
            rst = mathExpr;
            return true;
        }

        rst = nullptr;
        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchMathExpr(ref int index, out Expr? rst)
    bool Parser::MatchMathExpr(int& index, expr*& rst)
    {
        NCalculatorLibExprs::PlusExpr* plusExpr;
        if (MatchPlusExpr(index, plusExpr))
        {
            rst = plusExpr;
            return true;
        }

        NCalculatorLibExprs::mul_expr* mulExpr;
        if (MatchMulExpr(index, mulExpr))
        {
            rst = mulExpr;
            return true;
        }

        NCalculatorLibExprs::FunExpr* funExpr;
        if (MatchFunExpr(index, funExpr))
        {
            rst = funExpr;
            return true;
        }

        NCalculatorLibExprs::expr* quotedExpr;
        if (MatchQuoteExpr(index, quotedExpr))
        {
            rst = quotedExpr;
            return true;
        }

        NCalculatorLibExprs::UnitExpr* unitExpr;
        if (MatchUnitExpr(index, unitExpr))
        {
            rst = unitExpr;
            return true;
        }

        rst = nullptr;
        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchLogicExpr(ref int index, out Expr? rst)
    bool Parser::MatchLogicExpr(int& index, expr*& rst)
    {
        NCalculatorLibExprs::cond_expr* condExpr;
        if (MatchCondExpr(index, condExpr))
        {
            rst = condExpr;
            return true;
        }
        else
        {
            NCalculatorLibExprs::eq_expr* eqExpr;
            if (MatchEqExpr(index, eqExpr))
            {
                rst = eqExpr;
                return true;
            }
            else
            {
                NCalculatorLibExprs::RelExpr* relExpr;
                if (MatchRelExpr(index, relExpr))
                {
                    rst = relExpr;
                    return true;
                }
            }
        }

        rst = nullptr;
        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchCondExpr(ref int index, out CondExpr? rst)
    bool Parser::MatchCondExpr(int& index, cond_expr*& rst)
    {
        rst = nullptr;
        int tempindex1 = index;
        NCalculatorLibExprs::eq_expr* eqExpr;
        if (MatchEqExpr(tempindex1, eqExpr))
        {
            if (tempindex1 < getTokens().size() && getTokens()[tempindex1].Kind != token_kind::Question)
            {
                return false;
            }

            int tempindex2 = tempindex1 + 1;
            NCalculatorLibExprs::cond_expr* condExpr;
            if (MatchCondExpr(tempindex2, condExpr))
            {
                if (getTokens()[tempindex2].Kind != token_kind::Colon)
                {
                    return false;
                }

                int tempindex3 = tempindex2 + 1;
                NCalculatorLibExprs::cond_expr* condExpr2;
                if (MatchCondExpr(tempindex3, condExpr2))
                {
                    //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                    //ORIGINAL LINE: rst = new CondExpr(eqExpr!, condExpr!, condExpr2!);
                    rst = new cond_expr(eqExpr, condExpr, condExpr2);
                    index = tempindex3;
                    return true;
                }
                else
                {
                    NCalculatorLibExprs::expr* mathExpr;
                    if (MatchMathExpr(tempindex2, mathExpr))
                    {
                        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                        //ORIGINAL LINE: rst = new CondExpr(eqExpr!, condExpr!, mathExpr!);
                        rst = new cond_expr(eqExpr, condExpr, mathExpr);
                        index = tempindex3;
                        return true;
                    }
                }
            }
            else
            {
                NCalculatorLibExprs::expr* mathExpr2;
                if (MatchMathExpr(tempindex2, mathExpr2))
                {
                    if (getTokens()[tempindex2].Kind != token_kind::Colon)
                    {
                        return false;
                    }

                    int tempindex3 = tempindex2 + 1;
                    NCalculatorLibExprs::expr* mathExpr3;
                    if (MatchMathExpr(tempindex3, mathExpr3))
                    {
                        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                        //ORIGINAL LINE: rst = new CondExpr(eqExpr!, mathExpr2!, mathExpr3!);
                        rst = new cond_expr(eqExpr, mathExpr2, mathExpr3);
                        index = tempindex3;
                        return true;
                    }
                }
            }
        }
        else
        {
            NCalculatorLibExprs::RelExpr* relExpr;
            if (MatchRelExpr(tempindex1, relExpr))
            {
                if (getTokens()[tempindex1].Kind != token_kind::Question)
                {
                    return false;
                }

                int tempindex2 = tempindex1 + 1;

                NCalculatorLibExprs::cond_expr* condExpr;
                if (MatchCondExpr(tempindex2, condExpr))
                {
                    if (getTokens()[tempindex2].Kind != token_kind::Colon)
                    {
                        return false;
                    }

                    int tempindex3 = tempindex2 + 1;
                    NCalculatorLibExprs::cond_expr* condExpr2;
                    if (MatchCondExpr(tempindex3, condExpr2))
                    {
                        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                        //ORIGINAL LINE: rst = new CondExpr(relExpr!, condExpr!, condExpr2!);
                        rst = new cond_expr(relExpr, condExpr, condExpr2);
                        index = tempindex3;
                        return true;
                    }
                    else
                    {
                        NCalculatorLibExprs::expr* mathExpr;
                        if (MatchMathExpr(tempindex2, mathExpr))
                        {
                            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                            //ORIGINAL LINE: rst = new CondExpr(relExpr!, condExpr!, mathExpr!);
                            rst = new cond_expr(relExpr, condExpr, mathExpr);
                            index = tempindex3;
                            return true;
                        }
                    }
                }
                else
                {
                    NCalculatorLibExprs::expr* mathExpr2;
                    if (MatchMathExpr(tempindex2, mathExpr2))
                    {
                        if (getTokens()[tempindex2].Kind != token_kind::Colon)
                        {
                            return false;
                        }

                        int tempindex3 = tempindex2 + 1;
                        NCalculatorLibExprs::expr* mathExpr3;
                        if (MatchMathExpr(tempindex3, mathExpr3))
                        {
                            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                            //ORIGINAL LINE: rst = new CondExpr(relExpr!, mathExpr2!, mathExpr3!);
                            rst = new cond_expr(relExpr, mathExpr2, mathExpr3);
                            index = tempindex3;
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchEqExpr(ref int index, out EqExpr? rst)
    bool Parser::MatchEqExpr(int& index, eq_expr*& rst)
    {
        rst = nullptr;
        int tempindex1 = index;
        NCalculatorLibExprs::expr* mathExpr;
        if (MatchMathExpr(tempindex1, mathExpr))
        {
            if (tempindex1 >= getTokens().size())
            {
                return false;
            }

            auto optToken = getTokens()[tempindex1];
            if (optToken.Kind != token_kind::Eq && optToken.Kind != token_kind::NoEq)
            {
                return false;
            }

            int tempindex2 = tempindex1 + 1;
            NCalculatorLibExprs::eq_expr* relExpr2;
            if (MatchEqExpr(tempindex2, relExpr2))
            {
                //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                //ORIGINAL LINE: rst = new EqExpr(optToken, mathExpr!, relExpr2!);
                rst = new eq_expr(optToken, mathExpr, relExpr2);
                index = tempindex2;
                return true;
            }
            else
            {
                NCalculatorLibExprs::expr* mathExpr2;
                if (MatchMathExpr(tempindex2, mathExpr2))
                {
                    //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                    //ORIGINAL LINE: rst = new EqExpr(optToken, mathExpr!, mathExpr2!);
                    rst = new eq_expr(optToken, mathExpr, mathExpr2);
                    index = tempindex2;
                    return true;
                }
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchRelExpr(ref int index, out RelExpr? rst)
    bool Parser::MatchRelExpr(int& index, RelExpr*& rst)
    {
        rst = nullptr;
        int tempindex1 = index;
        NCalculatorLibExprs::expr* mathExpr;
        if (MatchMathExpr(tempindex1, mathExpr))
        {
            if (tempindex1 >= getTokens().size())
            {
                return false;
            }

            auto optToken = getTokens()[tempindex1];
            if (optToken.Kind != token_kind::Gtr && optToken.Kind != token_kind::GtrEq && optToken.Kind != token_kind::Lss && optToken.Kind != token_kind::LssEq)
            {
                return false;
            }

            int tempindex2 = tempindex1 + 1;
            NCalculatorLibExprs::RelExpr* relExpr2;
            if (MatchRelExpr(tempindex2, relExpr2))
            {
                //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                //ORIGINAL LINE: rst = new RelExpr(optToken, mathExpr!, relExpr2!);
                rst = new RelExpr(optToken, mathExpr, relExpr2);
                index = tempindex2;
                return true;
            }
            else
            {
                NCalculatorLibExprs::expr* mathExpr2;
                if (MatchMathExpr(tempindex2, mathExpr2))
                {
                    //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                    //ORIGINAL LINE: rst = new RelExpr(optToken, mathExpr!, mathExpr2!);
                    rst = new RelExpr(optToken, mathExpr, mathExpr2);
                    index = tempindex2;
                    return true;
                }
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchFunExpr(ref int index, out FunExpr? rst)
    bool Parser::MatchFunExpr(int& index, FunExpr*& rst)
    {
        rst = nullptr;
        if (index >= getTokens().size())
        {
            return false;
        }

        if (getTokens()[index].Kind != token_kind::Identifier)
        {
            return false;
        }

        int tempindex = index + 1;
        NCalculatorLibExprs::expr_seq_expr* expr;
        if (MatchQuoteExprSeqExpr(tempindex, expr))
        {
            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
            //ORIGINAL LINE: rst = new FunExpr(Tokens[index], expr!);
            rst = new FunExpr(getTokens()[index], expr);
            index = tempindex;
            return true;
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchQuoteExprSeqExpr(ref int index, out ExprSeqExpr? rst)
    bool Parser::MatchQuoteExprSeqExpr(int& index, expr_seq_expr*& rst)
    {
        rst = nullptr;
        if (index >= getTokens().size())
        {
            return false;
        }

        if (getTokens()[index].Kind != token_kind::LParen)
        {
            return false;
        }

        int tempindex = index + 1;
        NCalculatorLibExprs::expr_seq_expr* expr;
        if (MatchExprSeqExpr(tempindex, expr))
        {
            if (tempindex >= getTokens().size())
            {
                return false;
            }

            if (getTokens()[tempindex].Kind == token_kind::RParen)
            {
                rst = expr;
                index = tempindex + 1;
                return true;
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchQuoteExpr(ref int index, out Expr? rst)
    bool Parser::MatchQuoteExpr(int& index, expr*& rst)
    {
        rst = nullptr;
        if (index >= getTokens().size())
        {
            return false;
        }

        if (getTokens()[index].Kind != token_kind::LParen)
        {
            return false;
        }

        int tempindex = index + 1;
        NCalculatorLibExprs::expr* expr;
        if (MatchExpr(tempindex, expr))
        {
            if (tempindex >= getTokens().size())
            {
                return false;
            }

            if (getTokens()[tempindex].Kind == token_kind::RParen)
            {
                rst = expr;
                index = tempindex + 1;
                return true;
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchPlusExpr(ref int index, out PlusExpr? rst)
    bool Parser::MatchPlusExpr(int& index, PlusExpr*& rst)
    {
        rst = nullptr;
        int tempindex1 = index;
        NCalculatorLibExprs::mul_expr* mulExpr;
        if (MatchMulExpr(tempindex1, mulExpr))
        {
            if (tempindex1 >= getTokens().size())
            {
                return false;
            }

            auto optToken = getTokens()[tempindex1];
            if (optToken.Kind != token_kind::Plus && optToken.Kind != token_kind::Sub)
            {
                return false;
            }

            int tempindex2 = tempindex1 + 1;
            NCalculatorLibExprs::PlusExpr* plusExpr;
            if (MatchPlusExpr(tempindex2, plusExpr))
            {
                //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                //ORIGINAL LINE: rst = new PlusExpr(optToken, mulExpr!, plusExpr!);
                rst = new PlusExpr(optToken, mulExpr, plusExpr);
                index = tempindex2;
                return true;
            }
            else
            {
                NCalculatorLibExprs::mul_expr* mulExpr2;
                if (MatchMulExpr(tempindex2, mulExpr2))
                {
                    //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                    //ORIGINAL LINE: rst = new PlusExpr(optToken, mulExpr!, mulExpr2!);
                    rst = new PlusExpr(optToken, mulExpr, mulExpr2);
                    index = tempindex2;
                    return true;
                }
            }
        }
        else
        {
            NCalculatorLibExprs::UnitExpr* unitExpr;
            if (MatchUnitExpr(tempindex1, unitExpr))
            {
                if (tempindex1 >= getTokens().size())
                {
                    return false;
                }

                token optToken = getTokens()[tempindex1];
                if (optToken.Kind != token_kind::Plus && optToken.Kind != token_kind::Sub)
                {
                    return false;
                }

                int tempindex2 = tempindex1 + 1;
                NCalculatorLibExprs::PlusExpr* plusExpr;
                if (MatchPlusExpr(tempindex2, plusExpr))
                {
                    //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                    //ORIGINAL LINE: rst = new PlusExpr(plusExpr!.Operator, new PlusExpr(optToken, unitExpr!, plusExpr!.LeftExpr)!, plusExpr.RightExpr!);
                    PlusExpr tempVar(optToken, unitExpr, plusExpr->LeftExpr);
                    rst = new PlusExpr(plusExpr->Operator, &tempVar, plusExpr->RightExpr);
                    rst = bin_expr::SpinExpr(rst);

                    index = tempindex2;
                    return true;
                }
                else
                {
                    NCalculatorLibExprs::mul_expr* mulExpr2;
                    if (MatchMulExpr(tempindex2, mulExpr2))
                    {
                        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                        //ORIGINAL LINE: rst = new PlusExpr(optToken, unitExpr!, mulExpr2!);
                        rst = new PlusExpr(optToken, unitExpr, mulExpr2);
                        index = tempindex2;
                        return true;
                    }
                    else
                    {
                        NCalculatorLibExprs::UnitExpr* unitExpr2;
                        if (MatchUnitExpr(tempindex2, unitExpr2))
                        {
                            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                            //ORIGINAL LINE: rst = new PlusExpr(optToken, unitExpr!, unitExpr2!);
                            rst = new PlusExpr(optToken, unitExpr, unitExpr2);
                            index = tempindex2;
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchMulExpr(ref int index, out MulExpr? rst)
    bool Parser::MatchMulExpr(int& index, mul_expr*& rst)
    {
        rst = nullptr;
        int tempindex1 = index;

        // 匹配左侧是否是计算单元
        NCalculatorLibExprs::UnitExpr* unitExpr;
        if (MatchUnitExpr(tempindex1, unitExpr))
        {
            if (tempindex1 >= getTokens().size())
            {
                return false;
            }

            // 匹配是否是乘法符号 * / ^
            token optToken = getTokens()[tempindex1];
            if (optToken.Kind != token_kind::Mul && optToken.Kind != token_kind::Div && optToken.Kind != token_kind::Pow && optToken.Kind != token_kind::Mod)
            {
                return false;
            }

            int tempindex2 = tempindex1 + 1;
            NCalculatorLibExprs::mul_expr* mulExpr;
            if (MatchMulExpr(tempindex2, mulExpr))
            {
                //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                //ORIGINAL LINE: rst = new MulExpr(mulExpr!.Operator, new MulExpr(optToken, unitExpr!, mulExpr!.LeftExpr), mulExpr.RightExpr!);
                mul_expr tempVar(optToken, unitExpr, mulExpr->LeftExpr);
                rst = new mul_expr(mulExpr->Operator, &tempVar, mulExpr->RightExpr);
                rst = bin_expr::SpinExpr(rst);

                index = tempindex2;
                return true;
            }
            else
            {
                NCalculatorLibExprs::UnitExpr* unitExpr2;
                if (MatchUnitExpr(tempindex2, unitExpr2))
                {
                    //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                    //ORIGINAL LINE: rst = new MulExpr(optToken, unitExpr!, unitExpr2!);
                    rst = new mul_expr(optToken, unitExpr, unitExpr2);
                    index = tempindex2;
                    return true;
                }
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchUnitExpr(ref int index, out UnitExpr? rst)
    bool Parser::MatchUnitExpr(int& index, UnitExpr*& rst)
    {
        rst = nullptr;
        bool signed_Keyword;
        int tempindex = index;

        if (index >= getTokens().size())
        {
            return false;
        }

        signed_Keyword = getTokens()[index].Kind == token_kind::Sub;
        if (signed_Keyword)
        {
            tempindex++;
        }

        NCalculatorLibExprs::NumExpr* numExpr;
        if (MatchNumExpr(tempindex, numExpr))
        {
            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
            //ORIGINAL LINE: rst = new UnitExpr(numExpr!, signed);
            rst = new UnitExpr(numExpr, signed_Keyword);
            index = tempindex;
            return true;
        }
        else
        {
            NCalculatorLibExprs::FunExpr* funExpr;
            if (MatchFunExpr(tempindex, funExpr))
            {
                //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                //ORIGINAL LINE: rst = new UnitExpr(funExpr!, signed);
                rst = new UnitExpr(funExpr, signed_Keyword);
                index = tempindex;
                return true;
            }
            else
            {
                NCalculatorLibExprs::const_expr* constExpr;
                if (MatchConstExpr(tempindex, constExpr))
                {
                    //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                    //ORIGINAL LINE: rst = new UnitExpr(constExpr!, signed);
                    rst = new UnitExpr(constExpr, signed_Keyword);
                    index = tempindex;
                    return true;
                }
                else
                {
                    NCalculatorLibExprs::expr* quoteExpr;
                    if (MatchQuoteExpr(tempindex, quoteExpr))
                    {
                        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
                        //ORIGINAL LINE: rst = new UnitExpr(quoteExpr!, signed);
                        rst = new UnitExpr(quoteExpr, signed_Keyword);
                        index = tempindex;
                        return true;
                    }
                }
            }
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchNumExpr(ref int index, out NumExpr? rst)
    bool Parser::MatchNumExpr(int& index, NumExpr*& rst)
    {
        rst = nullptr;
        if (index >= getTokens().size())
        {
            return false;
        }

        if (getTokens()[index].Kind == token_kind::Number)
        {
            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
            //ORIGINAL LINE: rst = new NumExpr(Tokens[index].Value!);
            rst = new NumExpr(getTokens()[index].Value);
            index += 1;
            return true;
        }

        return false;
    }

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public bool MatchConstExpr(ref int index, out ConstExpr? rst)
    bool Parser::MatchConstExpr(int& index, const_expr*& rst)
    {
        rst = nullptr;
        if (index >= getTokens().size())
        {
            return false;
        }

        if (getTokens()[index].Kind == token_kind::Identifier)
        {
            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
            //ORIGINAL LINE: rst = new ConstExpr(Tokens[index].Value!);
            rst = new const_expr(getTokens()[index].Value);
            index += 1;
            return true;
        }

        return false;
    }

    expr* Parser::Parse()
    {
        int index = 0;
        NCalculatorLibExprs::expr* rst;
        if (MatchExpr(index, rst))
        {
            //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
            //ORIGINAL LINE: return rst!;
            return rst;
        }
        else
        {
            throw ArgumentOutOfRangeException();
        }
    }
}
