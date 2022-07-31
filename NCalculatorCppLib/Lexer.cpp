#include "Lexer.h"

using namespace NCalculator;

namespace NCalculatorLib
{

	TextReader *Lexer::getBaseReader() const
	{
		return baseReader;
	}

//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
//ORIGINAL LINE: public Lexer(TextReader tr)
	Lexer::Lexer(TextReader *tr) : baseReader((tr != nullptr) ? tr : throw std::invalid_argument("tr"))
	{
	}

	std::vector<Token> Lexer::Lex()
	{
		std::vector<Token> rst;

		while (true)
		{
			auto ch = baseReader->Read();
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
				StringBuilder *sb = new StringBuilder();
				sb->append(cch);

				while (true)
				{
					ch = baseReader->Peek();
					cch = static_cast<wchar_t>(ch);

					if (std::isalnum(cch))
					{
						baseReader->Read();
						sb->append(cch);
					}
					else
					{
						break;
					}
				}

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
				rst.push_back(Token(TokenKind::Identifier, sb->toString()));

				delete sb;
				continue;

				delete sb;
			}
			else if (std::isdigit(cch))
			{
				StringBuilder *sb = new StringBuilder();
				sb->append(cch);

				while (ch != -1)
				{
					ch = baseReader->Peek();
					cch = static_cast<wchar_t>(ch);
					if (ch >= L'0' && ch <= L'9')
					{
						baseReader->Read();
						sb->append(cch);
					}
					else
					{
						break;
					}
				}

				if (cch == L'.')
				{
					ch = baseReader->Read(); // skip '.'
					sb->append(cch);
					while (ch != -1)
					{
						ch = baseReader->Peek();
						cch = static_cast<wchar_t>(ch);
						if (ch >= L'0' && ch <= L'9')
						{
							baseReader->Read();
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
					baseReader->Read(); // skip 'e'
					sb->append(cch);

					ch = baseReader->Read();
					if (ch >= L'0' || ch <= L'9' || ch == L'+' || ch == L'-')
					{
						baseReader->Read();
						sb->append(static_cast<wchar_t>(ch));
					}

					while (ch != -1)
					{
						ch = baseReader->Peek();
						cch = static_cast<wchar_t>(ch);
						if (ch >= L'0' && ch <= L'9')
						{
							baseReader->Read();
							sb->append(cch);
						}
						else
						{
							break;
						}
					}
				}

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
				rst.push_back(Token(TokenKind::Number, sb->toString()));

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
						rst.push_back(Token(TokenKind::Plus, L""));
						break;
					case L'-':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::Sub, L""));
						break;
					case L'*':
						if (baseReader->Peek() == L'*')
						{
							baseReader->Read();
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::Pow, L""));
						}
						else
						{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::Mul, L""));
						}
						break;
					case L'/':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::Div, L""));
						break;
					case L'%':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::Mod, L""));
						break;
					case L'(':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::LParen, L""));
						break;
					case L')':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::RParen, L""));
						break;
					case L'?':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::Question, L""));
						break;
					case L':':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::Colon, L""));
						break;
					case L',':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::Comma, L""));
						break;
					case L'^':
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
						rst.push_back(Token(TokenKind::Pow, L""));
						break;
					case L'>':
						if (baseReader->Peek() == L'=')
						{
							baseReader->Read();
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::GtrEq, L""));
						}
						if (baseReader->Peek() == L'<')
						{
							baseReader->Read();
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::NoEq, L""));
						}
						else
						{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::Gtr, L""));
						}
						break;
					case L'<':
						if (baseReader->Peek() == L'=')
						{
							baseReader->Read();
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::LssEq, L""));
						}
						if (baseReader->Peek() == L'>')
						{
							baseReader->Read();
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::NoEq, L""));
						}
						else
						{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::Lss, L""));
						}
						break;
					case L'=':
						if (baseReader->Peek() == L'=')
						{
							baseReader->Read();
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::Eq, L""));
						}
						else
						{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
							rst.push_back(Token(TokenKind::Eq, L""));
						}
						break;
				}
			}
		}
	}
}
