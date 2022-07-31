#pragma once

#include <string>

namespace NCalculator
{
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
		Comma
	};

	class Token
	{
	public:
//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public Token(TokenKind kind, string? value)
		Token(TokenKind kind, const std::wstring &value);

		const TokenKind Kind;
//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public readonly string? Value;
		const std::wstring Value;

		std::wstring ToString();

		Token() : Kind(static_cast<NCalculator::TokenKind>(0)), Value(L"")
		{
		}
	};
}
