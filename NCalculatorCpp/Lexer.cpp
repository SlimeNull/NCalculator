#include<string>
#include<vector>
#include"Token.h"

std::vector<Token> lex(std::wstring& input) {
	std::vector<Token> tokens;
	std::vector<wchar_t> sb;

	for (size_t i = 0; i < input.length(); i++) {
		wchar_t ch = input[i];
		if (iswspace(ch)) {
			i++;
			continue;
		}
		else if (iswlower(ch) || isupper(ch)) {
			sb.clear();
			sb.push_back(ch);

			for (i++; i < input.length(); i++) {  // skip first char
				wchar_t _ch = input[i];

				if (iswlower(_ch) || iswupper(_ch) || iswdigit(_ch)) {
					sb.push_back(_ch);
				}
				else {
					break;
				}
			}

			i--;
			tokens.push_back(Token(TokenKind::Identifier, std::wstring(sb.begin(), sb.end())));
			continue;
		}
		else if (iswdigit(ch)) {
			sb.clear();
			sb.push_back(ch);

			for (i++; i < input.length(); i++) { // skip first char 
				ch = input[i];
				if (iswdigit(ch)) {
					sb.push_back(ch);
				}
				else {
					break;
				}
			}

			if (ch == '.') {
				sb.push_back(ch);
				for (i++; i < input.length(); i++) {
					ch = input[i];
					if (iswdigit(ch)) {
						sb.push_back(ch);
					}
					else {
						break;
					}
				}
			}

			if (ch == 'e' || ch == 'E') {
				sb.push_back(ch);
				
				i++;
				ch = input[i];
				if (i < input.length() && (iswdigit(ch) || ch == '+' || ch == '-')) {
					sb.push_back(ch);
				}

				for (i++; i < input.length(); i++) {
					ch = input[i];
					if (iswdigit(ch)) {
						sb.push_back(ch);
					}
					else {
						break;
					}
				}
			}

			tokens.push_back(Token(TokenKind::Number, std::wstring(sb.begin(), sb.end())));
			i--;
			continue;
		}
		else {
			switch (ch) {
				case '+':
					tokens.push_back(Token(TokenKind::Plus, L"+"));
					break;
				case '-':
					tokens.push_back(Token(TokenKind::Sub, L"-"));
					break;
				case '*':
					if (i + 1 < input.length() && input[i + 1] == '*') {
						tokens.push_back(Token(TokenKind::Pow, L"**"));
						i++;
					}
					else {
						tokens.push_back(Token(TokenKind::Mul, L"*"));
					}
					break;
				case '/':
					tokens.push_back(Token(TokenKind::Div, L"/"));
					break;
				case '(':
					tokens.push_back(Token(TokenKind::LParen, L"("));
					break;
				case ')':
					tokens.push_back(Token(TokenKind::RParen, L")"));
					break;
				case '?':
					tokens.push_back(Token(TokenKind::Question, L"?"));
					break;
				case ':':
					tokens.push_back(Token(TokenKind::Colon, L":"));
					break;
				case ',':
					tokens.push_back(Token(TokenKind::Comma, L","));
					break;
				case '^':
					tokens.push_back(Token(TokenKind::Pow, L"^"));
					break;
				case '>':
					if (i + 1 < input.length()) {
						switch (input[i + 1]) {
							case '=':
								i++;
								tokens.push_back(Token(TokenKind::GtrEq, L">="));
								break;
							case '<':
								i++;
								tokens.push_back(Token(TokenKind::NoEq, L"><"));
								break;
						}
					}

					tokens.push_back(Token(TokenKind::Gtr, L" "));
					break;
				case '<':
					if (i + 1 < input.length()) {
						switch (input[i + 1]) {
							case '=':
								i++;
								tokens.push_back(Token(TokenKind::LssEq, L"<="));
								break;
							case '>':
								i++;
								tokens.push_back(Token(TokenKind::NoEq, L"<>"));
								break;
						}
					}

					tokens.push_back(Token(TokenKind::Lss, L"<"));
					break;
				case '=':
					if (i + 1 < input.length()) {
						if (input[i + 1] == '=') {
							i++;
							tokens.push_back(Token(TokenKind::Eq, L"=="));
							break;
						}
					}
					
					tokens.push_back(Token(TokenKind::Eq, L"="));
					break;
			}
		}
	}

	return tokens;
}