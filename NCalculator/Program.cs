using NCalculatorLib;
using NCalculatorLib.Exprs;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Linq.Expressions;
using System.Text;

namespace NullLib.Calculator
{
    class Program
    {
        static void Main(string[] args)
        {
            Expression<Func<int, int, int>> someExpression = (a, b) => a + b;

            if (args.Length == 0)
            {
                Console.WriteLine("Calculator    By SlimeNull, 2022");
                Console.WriteLine("  Funs: abs ceil floor min max sum ln log log10 pow sqrt exp cbrt sin cos tan");
                Console.WriteLine("        asin acos atan sinh cosh tanh asinh acosh atanh round sign truncate fact");
                Console.WriteLine("  Opts: (...) * / % ** ^ + - > >= < <= == != & | .?.:.");
                Console.WriteLine();

#if DEBUG
                double count = 0;
                NCalcContext.Default.Variables["count"] = () => count++;
                NCalcContext.Default.Functions["myfunc"] = (values) => values.Sum();
#endif

                while (true)
                {
                    Console.Write(">>> ");
                    var input = Console.ReadLine();
                    if (string.IsNullOrEmpty(input))
                        return;

                    try
                    {
                        Console.WriteLine(NCalc.CompileEval(input));
                    }
                    catch(Exception ex)
                    {
                        Console.WriteLine($"Err: {ex.Message}");
                    }
                }
            }
            else
            {
                foreach (string exprstr in args)
                {
                    try
                    {
                        Console.WriteLine(NCalc.CompileEval(exprstr));
                    }
                    catch (Exception ex)
                    {
                        Console.WriteLine($"Err: {ex.Message}");
                        Environment.ExitCode--;
                    }
                }
            }
        }
    }
}
