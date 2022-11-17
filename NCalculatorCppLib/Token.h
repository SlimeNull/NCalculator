#pragma once

#include <string>

namespace NCalculator
{
	enum class token_kind
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

	class token
	{
	public:
//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public Token(TokenKind kind, string? value)
		token(token_kind kind, const std::wstring &value);

		const token_kind Kind;
//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public readonly string? Value;
		const std::wstring Value;

		std::wstring ToString();

		token() : Kind(static_cast<NCalculator::token_kind>(0)), Value(L"")
		{
		}
	};
}
