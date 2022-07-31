#pragma once

#include "Token.h"
#include "Exprs/ExprSeqExpr.h"
#include "Exprs/Expr.h"
#include "Exprs/CondExpr.h"
#include "Exprs/EqExpr.h"
#include "Exprs/RelExpr.h"
#include "Exprs/FunExpr.h"
#include "Exprs/PlusExpr.h"
#include "Exprs/MulExpr.h"
#include "Exprs/UnitExpr.h"
#include "Exprs/NumExpr.h"
#include "Exprs/ConstExpr.h"
#include <vector>
#include "exceptionhelper.h"

using namespace NCalculatorLibExprs;
using namespace NCalculator;



namespace NCalculatorLib
{
	class Parser
	{
	private:
		std::vector<Token> Tokens;

	public:
		std::vector<Token> getTokens() const;


		Parser(std::vector<Token> &tokens);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchExprSeqExpr(ref int index, out ExprSeqExpr? rst)
		bool MatchExprSeqExpr(int &index, ExprSeqExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchExpr(ref int index, out Expr? rst)
		bool MatchExpr(int &index, Expr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchMathExpr(ref int index, out Expr? rst)
		bool MatchMathExpr(int &index, Expr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchLogicExpr(ref int index, out Expr? rst)
		bool MatchLogicExpr(int &index, Expr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchCondExpr(ref int index, out CondExpr? rst)
		bool MatchCondExpr(int &index, CondExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchEqExpr(ref int index, out EqExpr? rst)
		bool MatchEqExpr(int &index, EqExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchRelExpr(ref int index, out RelExpr? rst)
		bool MatchRelExpr(int &index, RelExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchFunExpr(ref int index, out FunExpr? rst)
		bool MatchFunExpr(int &index, FunExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchQuoteExprSeqExpr(ref int index, out ExprSeqExpr? rst)
		bool MatchQuoteExprSeqExpr(int &index, ExprSeqExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchQuoteExpr(ref int index, out Expr? rst)
		bool MatchQuoteExpr(int &index, Expr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchPlusExpr(ref int index, out PlusExpr? rst)
		bool MatchPlusExpr(int &index, PlusExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchMulExpr(ref int index, out MulExpr? rst)
		bool MatchMulExpr(int &index, MulExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchUnitExpr(ref int index, out UnitExpr? rst)
		bool MatchUnitExpr(int &index, UnitExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchNumExpr(ref int index, out NumExpr? rst)
		bool MatchNumExpr(int &index, NumExpr *&rst);

//C# TO C++ CONVERTER WARNING: Nullable reference types have no equivalent in C++:
//ORIGINAL LINE: public bool MatchConstExpr(ref int index, out ConstExpr? rst)
		bool MatchConstExpr(int &index, ConstExpr *&rst);

		Expr *Parse();
	};
}
