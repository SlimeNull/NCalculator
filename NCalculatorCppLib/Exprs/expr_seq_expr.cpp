#include "ExprSeqExpr.h"

using namespace NCalculator;

namespace NCalculatorLibExprs
{

    expr_seq_expr::expr_seq_expr(std::vector<expr*> exprs)
    {
        if (exprs.size() < 1)
        {
            throw std::exception();
        }

        SeqValue = exprs;
    }

    expr* expr_seq_expr::operator [](int index)
    {
        return SeqValue[index];
    }

    double expr_seq_expr::eval()
    {
        return SeqValue[0]->eval();
    }

    std::vector<token> expr_seq_expr::enum_tokens()
    {
        std::vector<token> vec = std::vector<token>();

        for (int i = 0; i < SeqValue.size() - 1; i++)
        {
            for (auto token : SeqValue[i]->enum_tokens())
            {
                vec.push_back(token);
            }

            vec.push_back(token(token_kind::Comma, L""));
        }

        for (token token : SeqValue[SeqValue.size() - 1]->enum_tokens())
        {
            vec.push_back(token);
        }

        return vec;
    }
}
