#include "Expr.h"

using namespace NCalculatorLib;
using namespace NCalculator;

namespace NCalculatorLibExprs
{

	std::wstring expr::to_string()
	{
		return std::wstring::Join(L' ', enum_tokens());
	}
}
