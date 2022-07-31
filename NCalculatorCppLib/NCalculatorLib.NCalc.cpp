#include "NCalculatorLib.NCalc.h"
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "Exprs/Expr.h"

using namespace NCalculator;
using namespace NCalculatorLibExprs;

namespace NCalculatorLib
{

std::unordered_map<std::wstring, double> NCalc::DefaultConstants;
std::unordered_map<std::wstring, std::function<double()>*> NCalc::DefaultVariables;
std::unordered_map<std::wstring, std::function<double(std::vector<double>)>*> NCalc::DefaultFunctions;
std::unordered_map<std::wstring, double> NCalc::Constants;
std::unordered_map<std::wstring, std::function<double()>*> NCalc::Variables;
std::unordered_map<std::wstring, std::function<double(std::vector<double>)>*> NCalc::Functions;

	NCalc::StaticConstructor::StaticConstructor()
	{
		DefaultConstants = std::unordered_map<std::wstring, double>
		{
			{L"pi", M_PI},
			{L"e", M_E}
		};
		DefaultVariables =  {
			{L"date", [&]()
				{
					DateTime now = DateTime::Now;
					return now.Year * 10000 + now.Month * 100 + now.Day;
				}
			},
			{ L"time", [&] ()
				{
					DateTime now = DateTime::Now;
					return now.Hour * 10000000 + now.Minute * 100000 + now.Second * 1000 + now.Millisecond;
				}
			},
			{ L"timestamp", [&] ()
				{
					return DateTimeOffset::Now.ToUnixTimeSeconds();
				}
			}
		};
		DefaultFunctions = std::unordered_map<std::wstring, std::function<double(std::vector<double>)>*>
		{
			{L"abs", FunctionDefinition::Abs},
			{L"ceil", FunctionDefinition::Ceil},
			{L"floor", FunctionDefinition::Floor},
			{L"min", FunctionDefinition::Min},
			{L"max", FunctionDefinition::Max},
			{L"sum", FunctionDefinition::Sum},
			{L"ln", FunctionDefinition::Ln},
			{L"log", FunctionDefinition::Log},
			{L"log10", FunctionDefinition::Log10},
			{L"pow", FunctionDefinition::Pow},
			{L"sqrt", FunctionDefinition::Sqrt},
			{L"exp", FunctionDefinition::Exp},
			{L"cbrt", FunctionDefinition::Cbrt},
			{L"sin", FunctionDefinition::Sin},
			{L"cos", FunctionDefinition::Cos},
			{L"tan", FunctionDefinition::Tan},
			{L"asin", FunctionDefinition::Asin},
			{L"acos", FunctionDefinition::Acos},
			{L"atan", FunctionDefinition::Atan},
			{L"sinh", FunctionDefinition::Sinh},
			{L"cosh", FunctionDefinition::Cosh},
			{L"tanh", FunctionDefinition::Tanh},
			{L"asinh", FunctionDefinition::Asinh},
			{L"acosh", FunctionDefinition::Acosh},
			{L"atanh", FunctionDefinition::Atanh},
			{L"round", FunctionDefinition::Round},
			{L"sign", FunctionDefinition::Sign},
			{L"truncate", FunctionDefinition::Truncate},
			{L"fact", FunctionDefinition::Fact}
		};
	}

NCalc::StaticConstructor NCalc::staticConstructor;

	std::unordered_map<std::wstring, double> NCalc::getDefaultConstants()
	{
		return DefaultConstants;
	}

	std::unordered_map<std::wstring, std::function<double()>*> NCalc::getDefaultVariables()
	{
		return DefaultVariables;
	}

	std::unordered_map<std::wstring, std::function<double(std::vector<double>)>*> NCalc::getDefaultFunctions()
	{
		return DefaultFunctions;
	}

	std::unordered_map<std::wstring, double> NCalc::getConstants()
	{
		return Constants;
	}

	std::unordered_map<std::wstring, std::function<double()>*> NCalc::getVariables()
	{
		return Variables;
	}

	std::unordered_map<std::wstring, std::function<double(std::vector<double>)>*> NCalc::getFunctions()
	{
		return Functions;
	}

	double NCalc::Go(const std::wstring &expr)
	{
		Lexer tempVar(new StringReader(expr));
		std::vector<Token> tokens = (&tempVar)->Lex().ToArray();
		Parser tempVar2(tokens);
		Expr *_expr = (&tempVar2)->Parse();
		return _expr->Eval();
	}

	double NCalc::Go(Stream *exprStream)
	{
		Lexer tempVar(new StreamReader(exprStream));
		std::vector<Token> tokens = (&tempVar)->Lex().ToArray();
		Parser tempVar2(tokens);
		Expr *_expr = (&tempVar2)->Parse();
		return _expr->Eval();
	}

	double NCalc::FunctionDefinition::Abs(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::abs(args[0]);
	}

	double NCalc::FunctionDefinition::Ceil(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::ceil(args[0]);
	}

	double NCalc::FunctionDefinition::Floor(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::floor(args[0]);
	}

	double NCalc::FunctionDefinition::Min(std::vector<double> &args)
	{
		if (args.size() < 1)
		{
			throw std::invalid_argument("One parameter is required at least.");
		}
		return args.Min();
	}

	double NCalc::FunctionDefinition::Max(std::vector<double> &args)
	{
		if (args.size() < 1)
		{
			throw std::invalid_argument("One parameter is required at least.");
		}
		return args.Max();
	}

	double NCalc::FunctionDefinition::Sum(std::vector<double> &args)
	{
		if (args.size() < 1)
		{
			throw std::invalid_argument("One parameter is required at least.");
		}
		return args.Sum();
	}

	double NCalc::FunctionDefinition::Ln(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::log(args[0]);
	}

	double NCalc::FunctionDefinition::Log(std::vector<double> &args)
	{
		if (args.size() == 1)
		{
			return std::log(args[0]);
		}
		else if (args.size() == 2)
		{
			return Math::Log(args[0], args[1]);
		}
		else
		{
			throw std::invalid_argument("One or two parameters are required.");
		}
	}

	double NCalc::FunctionDefinition::Log10(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::log10(args[0]);
	}

	double NCalc::FunctionDefinition::Pow(std::vector<double> &args)
	{
		if (args.size() != 2)
		{
			throw std::invalid_argument("Two parameters are required.");
		}
		return std::pow(args[0], args[1]);
	}

	double NCalc::FunctionDefinition::Sqrt(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::sqrt(args[0]);
	}

	double NCalc::FunctionDefinition::Exp(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::exp(args[0]);
	}

	double NCalc::FunctionDefinition::Cbrt(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return Math::Cbrt(args[0]);
	}

	double NCalc::FunctionDefinition::Sin(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::sin(args[0]);
	}

	double NCalc::FunctionDefinition::Cos(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::cos(args[0]);
	}

	double NCalc::FunctionDefinition::Tan(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::tan(args[0]);
	}

	double NCalc::FunctionDefinition::Asin(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::asin(args[0]);
	}

	double NCalc::FunctionDefinition::Acos(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::acos(args[0]);
	}

	double NCalc::FunctionDefinition::Atan(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::atan(args[0]);
	}

	double NCalc::FunctionDefinition::Sinh(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::sinh(args[0]);
	}

	double NCalc::FunctionDefinition::Cosh(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::cosh(args[0]);
	}

	double NCalc::FunctionDefinition::Tanh(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::tanh(args[0]);
	}

	double NCalc::FunctionDefinition::Asinh(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return Math::Asinh(args[0]);
	}

	double NCalc::FunctionDefinition::Acosh(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return Math::Acosh(args[0]);
	}

	double NCalc::FunctionDefinition::Atanh(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return Math::Atanh(args[0]);
	}

	double NCalc::FunctionDefinition::Round(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return BankersRounding::round(args[0]);
	}

	double NCalc::FunctionDefinition::Sign(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return Math::Sign(args[0]);
	}

	double NCalc::FunctionDefinition::Truncate(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		return std::trunc(args[0]);
	}

	double NCalc::FunctionDefinition::Fact(std::vector<double> &args)
	{
		if (args.size() != 1)
		{
			throw std::invalid_argument("One parameter is required.");
		}
		double rst = 1;
		for (int i = 1; i <= args[0]; i++)
		{
			rst *= i;
		}

		return rst;
	}
}
