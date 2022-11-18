#include "NCalculatorLib.NCalc.h"
#include "Lexer.h"
#include "Token.h"
#include "Parser.h"
#include "Exprs/Expr.h"
#include <chrono>

using namespace NCalculator;
using namespace NCalculatorLibExprs;

namespace NCalculatorLib
{

    std::unordered_map<std::wstring, double> ncalc::DefaultConstants;
    std::unordered_map<std::wstring, std::function<double()>> ncalc::DefaultVariables;
    std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>> ncalc::DefaultFunctions;
    std::unordered_map<std::wstring, double> ncalc::Constants;
    std::unordered_map<std::wstring, std::function<double()>> ncalc::Variables;
    std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>> ncalc::Functions;

    ncalc::StaticConstructor::StaticConstructor()
    {
        DefaultConstants = std::unordered_map<std::wstring, double>
        {
            {L"pi", M_PI},
            {L"e", M_E}
        };
        DefaultVariables = std::unordered_map<std::wstring, std::function<double()>>
        {
            {L"date", []() -> double
                {
                    time_t _now = time(nullptr);
                    tm _tm;
                    localtime_s(&_tm, &_now);

                    return _tm.tm_year * 10000 + _tm.tm_mon * 100 + _tm.tm_mday;
                }
            },
            { L"time", []() -> double
                {
                    time_t _now = time(nullptr);
                    tm _tm;
                    localtime_s(&_tm, &_now);

                    return _tm.tm_hour * 10000000 + _tm.tm_min * 100000 + _tm.tm_sec * 1000 + 0;
                }
            },
            { L"timestamp", []() -> double
                {

                    return std::time(nullptr);
                }
            }
        };
        DefaultFunctions = std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>>
        {
            {L"abs", func_def::abs},
            {L"ceil", func_def::ceil},
            {L"floor", func_def::floor},
            {L"min", func_def::min},
            {L"max", func_def::max},
            {L"sum", func_def::sum},
            {L"ln", func_def::ln},
            {L"log", func_def::log},
            {L"log10", func_def::log10},
            {L"pow", func_def::pow},
            {L"sqrt", func_def::sqrt},
            {L"exp", func_def::exp},
            {L"cbrt", func_def::cbrt},
            {L"sin", func_def::sin},
            {L"cos", func_def::cos},
            {L"tan", func_def::tan},
            {L"asin", func_def::asin},
            {L"acos", func_def::acos},
            {L"atan", func_def::atan},
            {L"sinh", func_def::sinh},
            {L"cosh", func_def::cosh},
            {L"tanh", func_def::tanh},
            {L"asinh", func_def::asinh},
            {L"acosh", func_def::acosh},
            {L"atanh", func_def::atanh},
            {L"round", func_def::round},
            {L"sign", func_def::sign},
            {L"truncate", func_def::truncate},
            {L"fact", func_def::fact}
        };
    }

    ncalc::StaticConstructor ncalc::staticConstructor;

    std::unordered_map<std::wstring, double> ncalc::getDefaultConstants()
    {
        return DefaultConstants;
    }

    std::unordered_map<std::wstring, std::function<double()>> ncalc::getDefaultVariables()
    {
        return DefaultVariables;
    }

    std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>> ncalc::getDefaultFunctions()
    {
        return DefaultFunctions;
    }

    std::unordered_map<std::wstring, double> ncalc::getConstants()
    {
        return Constants;
    }

    std::unordered_map<std::wstring, std::function<double()>> ncalc::getVariables()
    {
        return Variables;
    }

    std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>> ncalc::getFunctions()
    {
        return Functions;
    }

    double ncalc::go(const std::wstring& expr)
    {
        lexer tempVar(new StringReader(expr));
        std::vector<token> tokens = (&tempVar)->Lex();
        Parser tempVar2(tokens);
        expr* _expr = (&tempVar2)->Parse();
        return _expr->Eval();
    }

    double ncalc::func_def::abs(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::abs(args[0]);
    }

    double ncalc::func_def::ceil(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::ceil(args[0]);
    }

    double ncalc::func_def::floor(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::floor(args[0]);
    }

    double ncalc::func_def::min(const std::vector<double>& args)
    {
        if (args.size() < 1)
        {
            throw std::invalid_argument("One parameter is required at least.");
        }

        double min = args[0];
        for (auto iter = args.begin() + 1; iter < args.end(); iter++) {
            if (*iter < min) {
                min = *iter;
            }
        }

        return min;
    }

    double ncalc::func_def::max(const std::vector<double>& args)
    {
        if (args.size() < 1)
        {
            throw std::invalid_argument("One parameter is required at least.");
        }

        double max = args[0];
        for (auto iter = args.begin() + 1; iter < args.end(); iter++) {
            if (*iter > max) {
                max = *iter;
            }
        }

        return max;
    }

    double ncalc::func_def::sum(const std::vector<double>& args)
    {
        if (args.size() < 1)
        {
            throw std::invalid_argument("One parameter is required at least.");
        }

        double sum = 0;
        for (auto iter = args.begin(); iter < args.end(); iter++) {
            sum += *iter;
        }

        return sum;
    }

    double ncalc::func_def::ln(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::log(args[0]);
    }

    double ncalc::func_def::log(const std::vector<double>& args)
    {
        if (args.size() == 1)
        {
            return std::log(args[0]);
        }
        else if (args.size() == 2)
        {
            return std::log(args[0]) / std::log(args[1]);
        }
        else
        {
            throw std::invalid_argument("One or two parameters are required.");
        }
    }

    double ncalc::func_def::log10(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::log10(args[0]);
    }

    double ncalc::func_def::pow(const std::vector<double>& args)
    {
        if (args.size() != 2)
        {
            throw std::invalid_argument("Two parameters are required.");
        }
        return std::pow(args[0], args[1]);
    }

    double ncalc::func_def::sqrt(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::sqrt(args[0]);
    }

    double ncalc::func_def::exp(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::exp(args[0]);
    }

    double ncalc::func_def::cbrt(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }

        return std::cbrt(args[0]);
    }

    double ncalc::func_def::sin(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::sin(args[0]);
    }

    double ncalc::func_def::cos(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::cos(args[0]);
    }

    double ncalc::func_def::tan(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::tan(args[0]);
    }

    double ncalc::func_def::asin(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::asin(args[0]);
    }

    double ncalc::func_def::acos(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::acos(args[0]);
    }

    double ncalc::func_def::atan(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::atan(args[0]);
    }

    double ncalc::func_def::sinh(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::sinh(args[0]);
    }

    double ncalc::func_def::cosh(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::cosh(args[0]);
    }

    double ncalc::func_def::tanh(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::tanh(args[0]);
    }

    double ncalc::func_def::asinh(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }

        return std::asinh(args[0]);
    }

    double ncalc::func_def::acosh(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::asinh(args[0]);
    }

    double ncalc::func_def::atanh(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::atanh(args[0]);
    }

    double ncalc::func_def::round(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return BankersRounding::round(args[0]);
    }

    double ncalc::func_def::sign(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }

        return args[0] < 0 ? -1 : 1;
    }

    double ncalc::func_def::truncate(const std::vector<double>& args)
    {
        if (args.size() != 1)
        {
            throw std::invalid_argument("One parameter is required.");
        }
        return std::trunc(args[0]);
    }

    double ncalc::func_def::fact(const std::vector<double>& args)
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
