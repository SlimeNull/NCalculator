#include "Token.h"

namespace NCalculator
{

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public Token(TokenKind kind, string? value)
	Token::Token(TokenKind kind, const std::wstring &value) : Kind(kind), Value(value)
	{
	}

	std::wstring Token::ToString()
	{
		if (Value != L"")
		{
			return Value;
		}

		std::wstring tempVar;
		switch (Kind)
		{
			case TokenKind::Identifier:
				tempVar = L"err";
				break;
			case TokenKind::Number:
				tempVar = L"0";
				break;
			case TokenKind::Plus:
				tempVar = L"+";
				break;
			case TokenKind::Sub:
				tempVar = L"-";
				break;
			case TokenKind::Mul:
				tempVar = L"*";
				break;
			case TokenKind::Div:
				tempVar = L"/";
				break;
			case TokenKind::Pow:
				tempVar = L"^";
				break;
			case TokenKind::Mod:
				tempVar = L"%";
				break;
			case TokenKind::LParen:
				tempVar = L"(";
				break;
			case TokenKind::RParen:
				tempVar = L")";
				break;
			case TokenKind::Gtr:
				tempVar = L">";
				break;
			case TokenKind::Lss:
				tempVar = L"<";
				break;
			case TokenKind::GtrEq:
				tempVar = L">=";
				break;
			case TokenKind::LssEq:
				tempVar = L"<=";
				break;
			case TokenKind::NoEq:
				tempVar = L"!=";
				break;
			case TokenKind::Eq:
				tempVar = L"==";
				break;
			case TokenKind::Colon:
				tempVar = L":";
				break;
			case TokenKind::Question:
				tempVar = L"?";
				break;
			case TokenKind::Comma:
				tempVar = L",";
				break;

			default:
				tempVar = L"";
				break;
		}
		return tempVar;
	}
}
