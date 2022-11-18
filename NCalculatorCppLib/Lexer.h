#pragma once

#include "Token.h"
#include <vector>
#include <cctype>
#include "stringbuilder.h"
#include "wstring_reader.h"

using namespace NCalculator;

namespace NCalculatorLib
{
    class lexer
    {
        private:
        wstring_reader* baseReader;

        public:
        virtual ~lexer()
        {

        }

        wstring_reader* getBaseReader() const;
        lexer();
        //C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
        //ORIGINAL LINE: public Lexer(TextReader tr)
        lexer(wstring_reader* const tr);

        std::vector<token> Lex();
    };
}
