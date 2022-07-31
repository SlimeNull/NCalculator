#include "Expr.h"

using namespace NCalculatorLib;
using namespace NCalculator;

namespace NCalculatorLibExprs
{

	std::wstring Expr::ToString()
	{
		return std::wstring::Join(L' ', EnumTokens());
	}
}
