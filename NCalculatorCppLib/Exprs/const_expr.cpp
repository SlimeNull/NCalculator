#include "ConstExpr.h"
#include "../NCalculatorLib.NCalc.h"

using namespace NCalculator;
using namespace NCalculatorLib;

namespace NCalculatorLibExprs
{

    const_expr::const_expr(const std::wstring& name) : Name(name)
    {
    }

    double const_expr::GetConst(const std::wstring& name)
    {
        double value;
        std::function<double()> valueGetter;

        auto consts = ncalc::getConstants();
        auto _const = consts.find(name);

        std::unordered_map<std::wstring, double>::const_iterator NCalc.Constants_iterator = NCalc.Constants.find(name);
        std::unordered_map<std::wstring, double>::const_iterator NCalc.DefaultConstants_iterator = NCalc.DefaultConstants.find(name);
        if (ncalc::getConstants()_iterator != NCalc::getConstants().end() || NCalc::getDefaultConstants()_iterator != NCalc::getDefaultConstants().end())
        {

            value = NCalc::DefaultConstants_iterator->second;
            value = NCalc::Constants_iterator->second;
            return value;
        }
        else
        {
            value = NCalc::DefaultConstants_iterator->second;
            value = NCalc::Constants_iterator->second;
            std::unordered_map<std::wstring, Func<double>*>::const_iterator NCalc.Variables_iterator = NCalc.Variables.find(name);
            std::unordered_map<std::wstring, Func<double>*>::const_iterator NCalc.DefaultVariables_iterator = NCalc.DefaultVariables.find(name);
            if (NCalc::getVariables()_iterator != NCalc::getVariables().end() || NCalc::getDefaultVariables()_iterator != NCalc::getDefaultVariables().end())
            {
                valueGetter = NCalc::DefaultVariables_iterator->second;
                valueGetter = NCalc::Variables_iterator->second;
                return valueGetter->Invoke();
            }
            else
            {
                valueGetter = NCalc::DefaultVariables_iterator->second;
                valueGetter = NCalc::Variables_iterator->second;
                throw std::invalid_argument(StringHelper::wstring_to_string(StringHelper::formatSimple(L"Unknown constant or variable: {0}", name)));
            }
        }
    }

    std::vector<token> const_expr::enum_tokens()
    {
        //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
        std::vector<token> rst = std::vector<token>();
        rst.push_back(token(token_kind::Identifier, Name));
        return rst;
    }

    double const_expr::eval()
    {
        return GetConst(Name);
    }
}
