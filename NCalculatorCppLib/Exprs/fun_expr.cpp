#include "FunExpr.h"
#include "../NCalculatorLib.NCalc.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

	FunExpr::FunExpr(token func, expr_seq_expr *param) : Func(func), Params(param)
	{
	}

	std::vector<token> FunExpr::enum_tokens()
	{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
		yield return Func;
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
		yield return Token(TokenKind::LParen, L"");

		for (auto token : *Params->enum_tokens())
		{
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
			yield return token;
		}

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
		yield return Token(TokenKind::RParen, L"");
	}

	double FunExpr::eval()
	{
//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: Func<double[], double>? func;
		Func<std::vector<double>, double> func;
	//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'null-forgiving operator':
	//ORIGINAL LINE: if (NCalc.Functions.TryGetValue(Func.Value!, out func) || NCalc.DefaultFunctions.TryGetValue(Func.Value!, out func))
		std::unordered_map<std::wstring, Func<std::vector<double>, double>*>::const_iterator NCalc.Functions_iterator = NCalc.Functions.find(Func.Value);
		std::unordered_map<std::wstring, Func<std::vector<double>, double>*>::const_iterator NCalc.DefaultFunctions_iterator = NCalc.DefaultFunctions.find(Func.Value);
		if (NCalc::getFunctions()_iterator != NCalc::getFunctions().end() || NCalc::getDefaultFunctions()_iterator != NCalc::getDefaultFunctions().end())
		{
			func = NCalc::DefaultFunctions_iterator->second;
			func = NCalc::Functions_iterator->second;
			return func->Invoke(Params->SeqValue.Select([&] (std::any expr)
			{
				expr::eval();
			})->ToArray());
		}
		else
		{
			func = NCalc::DefaultFunctions_iterator->second;
			func = NCalc::Functions_iterator->second;
			throw std::invalid_argument(StringHelper::wstring_to_string(StringHelper::formatSimple(L"Unknown function: {0}", Func.Value)));
		}
	}
}
