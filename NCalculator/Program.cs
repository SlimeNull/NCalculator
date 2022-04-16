using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;

namespace Null.Calculator
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Calculator    By SlimeNull, 2022");
            Console.WriteLine("  Funs: abs ceil floor min max ln log log10 sqrt exp sin cos tan asin acos atan sinh cosh tanh");
            Console.WriteLine("  Opts: (...) * / % ** ^ + - > >= < <= == != & | .?.:.");
            Console.WriteLine();
            
            while (true)
            {
                Console.Write(">>> ");
                var input = Console.ReadLine();
                if (string.IsNullOrEmpty(input))
                    return;

                Token[] tokens = new Lexer(new StringReader(input)).Lex().ToArray();
                Expr expr = new Parser(tokens).Parse();
                Console.WriteLine(expr.Eval());
            }
        }
    }
}
