#pragma once
#include<string>

enum class TokenKind
{
    Identifier,
    Number,

    Plus,
    Sub,
    Mul,
    Div,
    Pow,
    Mod,
    LParen,
    RParen,
    Gtr,
    Lss,
    GtrEq,
    LssEq,
    NoEq,
    Eq,
    Colon,
    Question,
    Comma,
};

class Token
{
public:
    TokenKind Kind;
    std::wstring Value;
	
	Token(TokenKind kind, std::wstring value) : Kind(kind), Value(value) {}
};

