#include "Lexer.h"

using namespace NCalculator;

namespace NCalculatorLib
{

    wstring_reader* lexer::getBaseReader() const
    {
        return baseReader;
    }

    lexer::lexer()
    {
        baseReader = new wstring_reader();
    }

    //C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
    //ORIGINAL LINE: public Lexer(TextReader tr)
    lexer::lexer(wstring_reader* const tr)
    {
        baseReader = tr;
    }

    std::vector<token> lexer::Lex()
    {
        std::vector<token> rst;

        while (true)
        {
            auto ch = baseReader->read();
            wchar_t cch = static_cast<wchar_t>(ch);

            if (ch == -1)
            {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                return rst;
            }

            if (std::isspace(cch))
            {
                continue;
            }
            else if (std::isalpha(cch))
            {
                StringBuilder* sb = new StringBuilder();
                sb->append(cch);

                while (true)
                {
                    ch = baseReader->peek();
                    cch = static_cast<wchar_t>(ch);

                    if (std::isalnum(cch))
                    {
                        baseReader->read();
                        sb->append(cch);
                    }
                    else
                    {
                        break;
                    }
                }

                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                rst.push_back(token(token_kind::Identifier, sb->toString()));

                delete sb;
                continue;

                delete sb;
            }
            else if (std::isdigit(cch))
            {
                StringBuilder* sb = new StringBuilder();
                sb->append(cch);

                while (ch != -1)
                {
                    ch = baseReader->peek();
                    cch = static_cast<wchar_t>(ch);
                    if (ch >= L'0' && ch <= L'9')
                    {
                        baseReader->read();
                        sb->append(cch);
                    }
                    else
                    {
                        break;
                    }
                }

                if (cch == L'.')
                {
                    ch = baseReader->read(); // skip '.'
                    sb->append(cch);
                    while (ch != -1)
                    {
                        ch = baseReader->peek();
                        cch = static_cast<wchar_t>(ch);
                        if (ch >= L'0' && ch <= L'9')
                        {
                            baseReader->read();
                            sb->append(cch);
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                if (cch == L'e' || cch == L'E')
                {
                    baseReader->read(); // skip 'e'
                    sb->append(cch);

                    ch = baseReader->read();
                    if (ch >= L'0' || ch <= L'9' || ch == L'+' || ch == L'-')
                    {
                        baseReader->read();
                        sb->append(static_cast<wchar_t>(ch));
                    }

                    while (ch != -1)
                    {
                        ch = baseReader->peek();
                        cch = static_cast<wchar_t>(ch);
                        if (ch >= L'0' && ch <= L'9')
                        {
                            baseReader->read();
                            sb->append(cch);
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                rst.push_back(token(token_kind::Number, sb->toString()));

                delete sb;
                continue;

                delete sb;
            }
            else
            {
                switch (ch)
                {
                    case L'+':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::Plus, L""));
                        break;
                    case L'-':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::Sub, L""));
                        break;
                    case L'*':
                        if (baseReader->peek() == L'*')
                        {
                            baseReader->read();
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::Pow, L""));
                        }
                        else
                        {
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::Mul, L""));
                        }
                        break;
                    case L'/':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::Div, L""));
                        break;
                    case L'%':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::Mod, L""));
                        break;
                    case L'(':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::LParen, L""));
                        break;
                    case L')':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::RParen, L""));
                        break;
                    case L'?':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::Question, L""));
                        break;
                    case L':':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::Colon, L""));
                        break;
                    case L',':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::Comma, L""));
                        break;
                    case L'^':
                        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                        rst.push_back(token(token_kind::Pow, L""));
                        break;
                    case L'>':
                        if (baseReader->peek() == L'=')
                        {
                            baseReader->read();
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::GtrEq, L""));
                        }
                        if (baseReader->peek() == L'<')
                        {
                            baseReader->read();
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::NoEq, L""));
                        }
                        else
                        {
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::Gtr, L""));
                        }
                        break;
                    case L'<':
                        if (baseReader->peek() == L'=')
                        {
                            baseReader->read();
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::LssEq, L""));
                        }
                        if (baseReader->peek() == L'>')
                        {
                            baseReader->read();
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::NoEq, L""));
                        }
                        else
                        {
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::Lss, L""));
                        }
                        break;
                    case L'=':
                        if (baseReader->peek() == L'=')
                        {
                            baseReader->read();
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::Eq, L""));
                        }
                        else
                        {
                            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                            rst.push_back(token(token_kind::Eq, L""));
                        }
                        break;
                }
            }
        }
    }
}
