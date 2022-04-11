using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;

namespace CalculatorPlus
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 1)
            {
                if (CalculatorPlus.TryCalculate(args[0], out double result))
                {
                    Console.WriteLine(result);
                    Environment.ExitCode = result != 0 ? 1 : 0;
                }
                else
                {
                    Console.WriteLine(0);
                    Environment.ExitCode = -1;
                }
            }
            else
            {
                Console.WriteLine("Calculator    By Null, 2020\nSupport Command Argument. Operators: () * / % ** + - > >= < <= == != & | .?.:.\n");
                while (true)
                {
                    Console.Write(">>> ");
                    if (CalculatorPlus.TryCalculate(Console.ReadLine(), out double result))
                    {
                        Console.WriteLine($"Result: {result}");
                        Environment.ExitCode = result != 0 ? 1 : 0;
                    }
                    else
                    {
                        CalculatorPlus.PrintErrorText();
                        Environment.ExitCode = -1;
                    }
                    Console.WriteLine();
                }
            }
        }
    }
}
