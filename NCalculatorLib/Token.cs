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
        public Token(TokenKind kind, string? value)
        {
            Kind = kind;
            Value = value;
        }

        public readonly TokenKind Kind;
        public readonly string? Value;

        public override string ToString()
        {
            if (Value != null)
                return Value;

            return Kind switch
            {
                TokenKind.Identifier => "err",
                TokenKind.Number => "0",
                TokenKind.Plus => "+",
                TokenKind.Sub => "-",
                TokenKind.Mul => "*",
                TokenKind.Div => "/",
                TokenKind.Pow => "^",
                TokenKind.Mod => "%",
                TokenKind.LParen => "(",
                TokenKind.RParen => ")",
                TokenKind.Gtr => ">",
                TokenKind.Lss => "<",
                TokenKind.GtrEq => ">=",
                TokenKind.LssEq => "<=",
                TokenKind.NoEq => "!=",
                TokenKind.Eq => "==",
                TokenKind.Colon => ":",
                TokenKind.Question => "?",
                TokenKind.Comma => ",",

                _ => string.Empty
            };
        }
    }
}
