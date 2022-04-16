using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Null.Calculator
{
    public enum TokenKind
    {
        Identifier,
        Number,
        
        Plus,
        Sub,
        Mul,
        Div,
        Pow,
        Mod,
        LParen,
        RParen,
        Gtr,
        Lss,
        GtrEq,
        LssEq,
        NoEq,
        Eq,
        Colon,
        Question,
        Comma,
    }
    
    public struct Token
    {
        public Token(TokenKind kind, string value)
        {
            Kind = kind;
            Value = value;
        }

        public readonly TokenKind Kind;
        public readonly string Value;
    }
}
