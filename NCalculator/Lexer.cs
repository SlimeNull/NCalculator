using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Null.Calculator
{
    public class Lexer
    {
        private readonly TextReader baseReader;

        public TextReader BaseReader => baseReader;
        public Lexer(TextReader tr)
        {
            baseReader = tr ?? throw new ArgumentNullException(nameof(tr));
        }

        public IEnumerable<Token> Lex()
        {
            while (true)
            {
                var ch = baseReader.Read();
                char cch = (char)ch;

                if (ch == -1)
                {
                    yield break;
                }

                if (char.IsWhiteSpace(cch))
                {
                    continue;
                }
                else if (char.IsLetter(cch))
                {
                    StringBuilder sb = new StringBuilder();
                    sb.Append(cch);

                    while (true)
                    {
                        ch = baseReader.Peek();
                        cch = (char)ch;

                        if (char.IsLetterOrDigit(cch))
                        {
                            baseReader.Read();
                            sb.Append(cch);
                        }
                        else
                        {
                            break;
                        }
                    }

                    yield return new Token(TokenKind.Identifier, sb.ToString());
                    continue;
                }
                else if (char.IsDigit(cch))
                {
                    StringBuilder sb = new StringBuilder();
                    sb.Append(cch);

                    while (ch != -1)
                    {
                        ch = baseReader.Peek();
                        cch = (char)ch;
                        if (ch >= '0' && ch <= '9')
                        {
                            baseReader.Read();
                            sb.Append(cch);
                        }
                        else
                        {
                            break;
                        }
                    }

                    if (cch == '.')
                    {
                        ch = baseReader.Read();  // skip '.'
                        sb.Append(cch);
                        while (ch != -1)
                        {
                            ch = baseReader.Peek();
                            cch = (char)ch;
                            if (ch >= '0' && ch <= '9')
                            {
                                baseReader.Read();
                                sb.Append(cch);
                            }
                            else
                            {
                                break;
                            }
                        }
                    }

                    if (cch == 'e' || cch == 'E')
                    {
                        baseReader.Read();  // skip 'e'
                        sb.Append(cch);

                        ch = baseReader.Read();
                        if (ch >= '0' || ch <= '9' || ch == '+' || ch == '-')
                        {
                            baseReader.Read();
                            sb.Append((char)ch);
                        }

                        while (ch != -1)
                        {
                            ch = baseReader.Peek();
                            cch = (char)ch;
                            if (ch >= '0' && ch <= '9')
                            {
                                baseReader.Read();
                                sb.Append(cch);
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                    
                    yield return new Token(TokenKind.Number, sb.ToString());
                    continue;
                }
                else
                {
                    switch (ch)
                    {
                        case '+':
                            yield return new Token(TokenKind.Plus, null);
                            break;
                        case '-':
                            yield return new Token(TokenKind.Sub, null);
                            break;
                        case '*':
                            if (baseReader.Peek() == '*')
                            {
                                baseReader.Read();
                                yield return new Token(TokenKind.Pow, null);
                            }
                            else
                            {
                                yield return new Token(TokenKind.Mul, null);
                            }
                            break;
                        case '/':
                            yield return new Token(TokenKind.Div, null);
                            break;
                        case '(':
                            yield return new Token(TokenKind.LParen, null);
                            break;
                        case ')':
                            yield return new Token(TokenKind.RParen, null);
                            break;
                        case '?':
                            yield return new Token(TokenKind.Question, null);
                            break;
                        case ':':
                            yield return new Token(TokenKind.Colon, null);
                            break;
                        case ',':
                            yield return new Token(TokenKind.Comma, null);
                            break;
                        case '^':
                            yield return new Token(TokenKind.Pow, null);
                            break;
                        case '>':
                            if (baseReader.Peek() == '=')
                            {
                                baseReader.Read();
                                yield return new Token(TokenKind.GtrEq, null);
                            }
                            if (baseReader.Peek() == '<')
                            {
                                baseReader.Read();
                                yield return new Token(TokenKind.NoEq, null);
                            }
                            else
                            {
                                yield return new Token(TokenKind.Gtr, null);
                            }
                            break;
                        case '<':
                            if (baseReader.Peek() == '=')
                            {
                                baseReader.Read();
                                yield return new Token(TokenKind.LssEq, null);
                            }
                            if (baseReader.Peek() == '>')
                            {
                                baseReader.Read();
                                yield return new Token(TokenKind.NoEq, null);
                            }
                            else
                            {
                                yield return new Token(TokenKind.Lss, null);
                            }
                            break;
                        case '=':
                            if (baseReader.Peek() == '=')
                            {
                                baseReader.Read();
                                yield return new Token(TokenKind.Eq, null);
                            }
                            else
                            {
                                yield return new Token(TokenKind.Eq, null);
                            }
                            break;
                    }
                }
            }
        }
    }
}