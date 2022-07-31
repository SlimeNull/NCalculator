using Null.Calculator;
using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualBasic;
using NCalculatorLib.Exprs;

namespace NCalculatorLib
{
    public static partial class NCalc
    {
        static NCalc()
        {
            DefaultConstants = new Dictionary<string, double>()
            {
                { "pi", Math.PI },
                { "e", Math.E },
            };
            DefaultVariables = new Dictionary<string, Func<double>>()
            {
                { "date", () =>
                    {
                        DateTime now = DateTime.Now;
                        return now.Year * 10000 +
                               now.Month * 100 +
                               now.Day;
                    }
                },
                { "time", () =>
                    {
                        DateTime now = DateTime.Now;
                        return now.Hour * 10000000 +
                               now.Minute * 100000 +
                               now.Second * 1000 +
                               now.Millisecond;
                    }
                },
                { "timestamp", () =>
                    {
                        return DateTimeOffset.Now.ToUnixTimeSeconds();
                    }
                }
            };
            DefaultFunctions = new Dictionary<string, Func<double[], double>>()
            {
                { "abs", FunctionDefinition.Abs },
                { "ceil", FunctionDefinition.Ceil },
                { "floor", FunctionDefinition.Floor },
                { "min", FunctionDefinition.Min },
                { "max", FunctionDefinition.Max },
                { "sum", FunctionDefinition.Sum },
                { "ln", FunctionDefinition.Ln },
                { "log", FunctionDefinition.Log },
                { "log10", FunctionDefinition.Log10 },
                { "pow", FunctionDefinition.Pow },
                { "sqrt", FunctionDefinition.Sqrt },
                { "exp", FunctionDefinition.Exp },
                { "cbrt", FunctionDefinition.Cbrt },
                { "sin", FunctionDefinition.Sin },
                { "cos", FunctionDefinition.Cos },
                { "tan", FunctionDefinition.Tan },
                { "asin", FunctionDefinition.Asin },
                { "acos", FunctionDefinition.Acos },
                { "atan", FunctionDefinition.Atan },
                { "sinh", FunctionDefinition.Sinh },
                { "cosh", FunctionDefinition.Cosh },
                { "tanh", FunctionDefinition.Tanh },
                { "asinh", FunctionDefinition.Asinh },
                { "acosh", FunctionDefinition.Acosh },
                { "atanh", FunctionDefinition.Atanh },
                { "round", FunctionDefinition.Round },
                { "sign", FunctionDefinition.Sign },
                { "truncate", FunctionDefinition.Truncate },

                { "fact", FunctionDefinition.Fact },
            };
        }

        internal static Dictionary<string, double> DefaultConstants { get; }
        internal static Dictionary<string, Func<double>> DefaultVariables { get; }
        internal static Dictionary<string, Func<double[], double>> DefaultFunctions { get; }

        public static Dictionary<string, double> Constants { get; } = new Dictionary<string, double>();
        public static Dictionary<string, Func<double>> Variables { get; } = new Dictionary<string, Func<double>>();
        public static Dictionary<string, Func<double[], double>> Functions { get; } = new Dictionary<string, Func<double[], double>>();

        public static double Go(string expr)
        {
            Token[] tokens = new Lexer(new StringReader(expr)).Lex().ToArray();
            Expr _expr = new Parser(tokens).Parse();
            return _expr.Eval();
        }

        public static double Go(Stream exprStream)
        {
            Token[] tokens = new Lexer(new StreamReader(exprStream)).Lex().ToArray();
            Expr _expr = new Parser(tokens).Parse();
            return _expr.Eval();
        }
    }
}
