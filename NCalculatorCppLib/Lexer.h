#pragma once

#include "Token.h"
#include <vector>
#include <cctype>
#include "stringbuilder.h"

using namespace NCalculator;

namespace NCalculatorLib
{
	class Lexer
	{
	private:
		TextReader *const baseReader;

	public:
		virtual ~Lexer()
		{
			delete baseReader;
		}

		TextReader *getBaseReader() const;
//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
//ORIGINAL LINE: public Lexer(TextReader tr)
		Lexer(TextReader *tr);

		std::vector<Token> Lex();
	};
}
