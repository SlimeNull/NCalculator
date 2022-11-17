#include "Token.h"

namespace NCalculator
{

    //C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
    //ORIGINAL LINE: public Token(TokenKind kind, string? value)
    token::token(token_kind kind, const std::wstring& value) : Kind(kind), Value(value)
    {
    }

    std::wstring token::ToString()
    {
        if (Value != L"")
        {
            return Value;
        }

        std::wstring tempVar;
        switch (Kind)
        {
            case token_kind::Identifier:
                tempVar = L"err";
                break;
            case token_kind::Number:
                tempVar = L"0";
                break;
            case token_kind::Plus:
                tempVar = L"+";
                break;
            case token_kind::Sub:
                tempVar = L"-";
                break;
            case token_kind::Mul:
                tempVar = L"*";
                break;
            case token_kind::Div:
                tempVar = L"/";
                break;
            case token_kind::Pow:
                tempVar = L"^";
                break;
            case token_kind::Mod:
                tempVar = L"%";
                break;
            case token_kind::LParen:
                tempVar = L"(";
                break;
            case token_kind::RParen:
                tempVar = L")";
                break;
            case token_kind::Gtr:
                tempVar = L">";
                break;
            case token_kind::Lss:
                tempVar = L"<";
                break;
            case token_kind::GtrEq:
                tempVar = L">=";
                break;
            case token_kind::LssEq:
                tempVar = L"<=";
                break;
            case token_kind::NoEq:
                tempVar = L"!=";
                break;
            case token_kind::Eq:
                tempVar = L"==";
                break;
            case token_kind::Colon:
                tempVar = L":";
                break;
            case token_kind::Question:
                tempVar = L"?";
                break;
            case token_kind::Comma:
                tempVar = L",";
                break;

            default:
                tempVar = L"";
                break;
        }
        return tempVar;
    }
}
