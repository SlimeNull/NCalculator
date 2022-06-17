using NCalculatorLib;
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
            if (args.Length == 0)
            {
                Console.WriteLine("Calculator    By SlimeNull, 2022");
                Console.WriteLine("  Funs: ﻿abs ceil floor min max sum ln log log10 pow sqrt exp cbrt sin cos tan");
                Console.WriteLine("        asin acos atan sinh cosh tanh asinh acosh atanh round sign truncate");
                Console.WriteLine("  Opts: (...) * / % ** ^ + - > >= < <= == != & | .?.:.");
                Console.WriteLine();

#if DEBUG
                double count = 0;
                NCalc.Variables["count"] = () => count++;
                NCalc.Functions["myfunc"] = (values) => values.Sum();
#endif

                while (true)
                {
                    Console.Write(">>> ");
                    var input = Console.ReadLine();
                    if (string.IsNullOrEmpty(input))
                        return;

                    Console.WriteLine(NCalc.Go(input));
                }
            }
            else
            {
                foreach (string exprstr in args)
                {
                    Console.WriteLine(NCalc.Go(exprstr));
                }
            }
        }
    }
}
