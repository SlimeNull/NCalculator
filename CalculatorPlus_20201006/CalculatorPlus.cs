using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CalculatorPlus_20201006
{
    class CalculatorPlus
    {
        public enum CalcTokenType
        {
            None, Number = 1, Operator = 2, Expression = 4
        }
        enum CalcOperator
        {
            None,
            Add = 1,
            Sub = 2,
            Mul = 4,
            Div = 8,
            Mod = 16,
            Pow = 32,
            Lss = 64,
            Gtr = 128,
            Leq = 256,
            Geq = 512,
            Equ = 1024,
            Neq = 2048,
            Not = 4096,
            And = 8192,
            Or = 16384,
            If = 32768,
            Witch = 65536
        }
        public class CalcToken
        {
            public CalcToken(CalcTokenType type, object content)
            {
                this.type = type;
                this.content = content;
            }
            CalcTokenType type;
            object content;
            public CalcTokenType Type
            {
                get
                {
                    return type;
                }
            }
            public object Content
            {
                get
                {
                    return content;
                }
            }
            public string ToInfoText()
            {
                switch (type)
                {
                    case CalcTokenType.None:
                        return $"<CalcToken Type:None Content:Null />";
                    case CalcTokenType.Number:
                        return $"<CalcToken Type:Number Content:{content} />";
                    case CalcTokenType.Operator:
                        return $"<CalcToken Type:Operator Content:{content} />";
                    case CalcTokenType.Expression:
                        return $"<CalcToken Type:Expression Content:[{string.Join(", ", content)}] />";
                    default:
                        return $"<CalcToken Uninitialized />";
                }
            }
            public override string ToString()
            {
                switch (type)
                {
                    case CalcTokenType.None:
                        return string.Empty;
                    case CalcTokenType.Number:
                        return content.ToString();
                    case CalcTokenType.Operator:
                        if (content is CalcOperator)
                        {
                            return IGetOperatorText((CalcOperator)content);
                        }
                        else
                        {
                            return string.Empty;
                        }
                    case CalcTokenType.Expression:
                        return string.Join(" ", content);
                    default:
                        return string.Empty;
                }
            }
        }

        char[] OperatorChars = "+-*/<>!=&|?:".ToArray();
        char[] NumberChars = "0123456789.".ToArray();
        char[] EmptyChars = " \n\r\t".ToArray();

        List<string> errors = new List<string>();


        // 下面是分词核心
        bool TryParseCalcTokens(ref char[] source, ref int offset, out List<CalcToken> result, bool inner = false, int level = 0)
        {
            result = new List<CalcToken>();

            for (; offset < source.Length; offset++)
            {
                if (EmptyChars.Contains(source[offset]))
                {
                    continue;
                }
                else if (source[offset] == '(')
                {
                    offset++;
                    if (TryParseCalcTokens(ref source, ref offset, out List<CalcToken> newrst, true, level + 1))
                    {
                        result.Add(new CalcToken(CalcTokenType.Expression, newrst));
                    }
                    else
                    {
                        errors.Add($"Error when parsing inner expression. Level:{level};");
                        return false;
                    }
                }
                else if (source[offset] == ')')
                {
                    return true;
                }
                else
                {
                    if (TryParseToken(ref source, ref offset, out CalcToken newcctk))
                    {
                        result.Add(newcctk);
                    }
                    else
                    {
                        errors.Add($"Error when parsing expression token. Level:{level};");
                        return false;
                    }
                }
            }


            return true;
        }
        bool TryParseToken(ref char[] source, ref int offset, out CalcToken result)
        {
            while (EmptyChars.Contains(source[offset]))
            {
                offset++;
            }
            if (NumberChars.Contains(source[offset]))
            {
                if (TryParseNumberToken(ref source, ref offset, out double newnum))
                {
                    result = new CalcToken(CalcTokenType.Number, newnum);
                    return true;
                }
                else
                {
                    result = new CalcToken(CalcTokenType.None, null);
                    return false;
                }
            }
            else if (OperatorChars.Contains(source[offset]))
            {
                if (TryParseOperatorToken(ref source, ref offset, out CalcOperator newopt))
                {
                    result = new CalcToken(CalcTokenType.Operator, newopt);
                    return true;
                }
                else
                {
                    result = new CalcToken(CalcTokenType.None, null);
                    return false;
                }
            }
            else
            {
                errors.Add($"Unknown char '{source[offset]}' for parsing token. Index:{offset};");
                result = new CalcToken(CalcTokenType.None, null);
                return false;
            }
        }
        bool TryParseNumberToken(ref char[] source, ref int offset, out double result)
        {
            result = 0;

            bool parsing = false;
            StringBuilder builder = new StringBuilder();

            for (; offset < source.Length; offset++)
            {
                if (parsing)
                {
                    if (NumberChars.Contains(source[offset]))
                    {
                        builder.Append(source[offset]);
                    }
                    else
                    {
                        offset--;                   // 索引不可超过本类型数据的范围, 故减一
                        return double.TryParse(builder.ToString(), out result);
                    }
                }
                else
                {
                    if (NumberChars.Contains(source[offset]))
                    {
                        parsing = true;
                        builder.Append(source[offset]);
                    }
                    else if (EmptyChars.Contains(source[offset]))
                    {
                        continue;
                    }
                    else
                    {
                        errors.Add($"Invalid char '{source[offset]}' when parsing number. Index:{offset};");
                        return false;
                    }
                }
            }

            return double.TryParse(builder.ToString(), out result);
        }
        bool TryParseOperatorToken(ref char[] source, ref int offset, out CalcOperator result)
        {
            result = 0;

            bool parsing = false;
            StringBuilder builder = new StringBuilder();

            for (; offset < source.Length; offset++)
            {
                if (parsing)
                {
                    if (OperatorChars.Contains(source[offset]))
                    {
                        builder.Append(source[offset]);
                    }
                    else
                    {
                        offset--;
                        return ITryGetOperator(builder.ToString(), out result);
                    }
                }
                else
                {
                    if (OperatorChars.Contains(source[offset]))
                    {
                        parsing = true;
                        builder.Append(source[offset]);
                    }
                    else if (EmptyChars.Contains(source[offset]))
                    {
                        continue;
                    }
                    else
                    {
                        errors.Add($"Invalid char '{source[offset]}' when parsing operator. Index:{offset};");
                        return false;
                    }
                }
            }

            return ITryGetOperator(builder.ToString(), out result);
        }
        bool ITryGetOperator(string str, out CalcOperator result)
        {
            switch (str.ToString())
            {
                case "+":
                    result = CalcOperator.Add;
                    return true;
                case "-":
                    result = CalcOperator.Sub;
                    return true;
                case "*":
                    result = CalcOperator.Mul;
                    return true;
                case "/":
                    result = CalcOperator.Div;
                    return true;
                case "%":
                    result = CalcOperator.Mod;
                    return true;
                case "**":
                    result = CalcOperator.Pow;
                    return true;
                case "<":
                    result = CalcOperator.Lss;
                    return true;
                case ">":
                    result = CalcOperator.Gtr;
                    return true;
                case ">=":
                    result = CalcOperator.Geq;
                    return true;
                case "<=":
                    result = CalcOperator.Leq;
                    return true;
                case "!":
                    result = CalcOperator.Not;
                    return true;
                case "=":
                    result = CalcOperator.Equ;
                    return true;
                case "==":
                    result = CalcOperator.Equ;
                    return true;
                case "!=":
                    result = CalcOperator.Neq;
                    return true;
                case "&":
                    result = CalcOperator.And;
                    return true;
                case "&&":
                    result = CalcOperator.And;
                    return true;
                case "|":
                    result = CalcOperator.Or;
                    return true;
                case "||":
                    result = CalcOperator.Or;
                    return true;
                case "?":
                    result = CalcOperator.If;
                    return true;
                case ":":
                    result = CalcOperator.Witch;
                    return true;
                default:
                    result = CalcOperator.None;
                    errors.Add($"Unsupported operator '{str}';");
                    return false;
            }
        }
        static string IGetOperatorText(CalcOperator opt)
        {
            switch (opt)
            {
                case CalcOperator.None:
                    return string.Empty;
                case CalcOperator.Add:
                    return "+";
                case CalcOperator.Sub:
                    return "-";
                case CalcOperator.Mul:
                    return "*";
                case CalcOperator.Div:
                    return "/";
                case CalcOperator.Mod:
                    return "%";
                case CalcOperator.Pow:
                    return "^";
                case CalcOperator.Lss:
                    return "<";
                case CalcOperator.Gtr:
                    return ">";
                case CalcOperator.Leq:
                    return "<=";
                case CalcOperator.Geq:
                    return ">=";
                case CalcOperator.Equ:
                    return "=";
                case CalcOperator.Neq:
                    return "!=";
                case CalcOperator.Not:
                    return "!";
                case CalcOperator.And:
                    return "&";
                case CalcOperator.Or:
                    return "|";
                case CalcOperator.If:
                    return "?";
                case CalcOperator.Witch:
                    return ":";
                default:
                    return string.Empty;
            }
        }

        // 下面是运算核心
        bool TryCalculateTokens(ref List<CalcToken> source, out double result, out List<string> errors)
        {
            errors = new List<string>();
            result = 0;

            for (int i = 0; i < source.Count; i++)
            {
                if (source[i].Type == CalcTokenType.Operator && CheckOperator(CalcOperator.Mul | CalcOperator.Div | CalcOperator.Mod | CalcOperator.Pow, (CalcOperator)source[i].Content) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, -1) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, 1))
                {
                    if (TryGetTokenValue(ref errors, source[i - 1], out double leftnum) && TryGetTokenValue(ref errors, source[i + 1], out double rightnum))
                    {
                        double tmpnum = 0;
                        switch ((CalcOperator)source[i].Content)
                        {
                            case CalcOperator.Mul:
                                tmpnum = leftnum * rightnum;
                                break;
                            case CalcOperator.Div:
                                tmpnum = leftnum / rightnum;
                                break;
                            case CalcOperator.Mod:
                                tmpnum = leftnum % rightnum;
                                break;
                            case CalcOperator.Pow:
                                tmpnum = Math.Pow(leftnum, rightnum);
                                break;
                            default:
                                throw new Exception();
                        }
                        source[i - 1] = new CalcToken(CalcTokenType.Number, tmpnum);
                        source.RemoveRange(i, 2);
                        i--;
                    }
                    else
                    {
                        errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                        return false;
                    }
                }
            }    // * / % **
            for (int i = 0; i < source.Count; i++)
            {
                if (source[i].Type == CalcTokenType.Operator && CheckOperator(CalcOperator.Add | CalcOperator.Sub, (CalcOperator)source[i].Content) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, 1))
                {
                    if (CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, -1))
                    {
                        if (TryGetTokenValue(ref errors, source[i - 1], out double leftnum) && TryGetTokenValue(ref errors, source[i + 1], out double rightnum))
                        {
                            double tmpnum = 0;
                            switch ((CalcOperator)source[i].Content)
                            {
                                case CalcOperator.Add:
                                    tmpnum = leftnum + rightnum;
                                    break;
                                case CalcOperator.Sub:
                                    tmpnum = leftnum - rightnum;
                                    break;
                                default:
                                    throw new Exception();
                            }
                            source[i - 1] = new CalcToken(CalcTokenType.Number, tmpnum);
                            source.RemoveRange(i, 2);
                            i--;
                        }
                        else
                        {
                            errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                            return false;
                        }
                    }
                    else
                    {
                        if (TryGetTokenValue(ref errors, source[i + 1], out double rightnum))
                        {
                            double tmpnum = 0;
                            switch ((CalcOperator)source[i].Content)
                            {
                                case CalcOperator.Add:
                                    tmpnum = rightnum;
                                    break;
                                case CalcOperator.Sub:
                                    tmpnum = 0 - rightnum;
                                    break;
                                default:
                                    throw new Exception();
                            }
                            source[i] = new CalcToken(CalcTokenType.Number, tmpnum);
                            source.RemoveRange(i + 1, 1);
                        }
                        else
                        {
                            errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                            return false;
                        }
                    }
                }
            }    // + -
            for (int i = 0; i < source.Count; i++)
            {
                if (source[i].Type == CalcTokenType.Operator && CheckOperator(CalcOperator.Gtr | CalcOperator.Lss | CalcOperator.Geq | CalcOperator.Leq, (CalcOperator)source[i].Content) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, -1) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, 1))
                {
                    if (TryGetTokenValue(ref errors, source[i - 1], out double leftnum) && TryGetTokenValue(ref errors, source[i + 1], out double rightnum))
                    {
                        double tmpnum = 0;
                        switch ((CalcOperator)source[i].Content)
                        {
                            case CalcOperator.Gtr:
                                tmpnum = leftnum > rightnum ? 1 : 0;
                                break;
                            case CalcOperator.Lss:
                                tmpnum = leftnum < rightnum ? 1 : 0;
                                break;
                            case CalcOperator.Geq:
                                tmpnum = leftnum >= rightnum ? 1 : 0;
                                break;
                            case CalcOperator.Leq:
                                tmpnum = leftnum <= rightnum ? 1 : 0;
                                break;
                            default:
                                throw new Exception();
                        }
                        source[i - 1] = new CalcToken(CalcTokenType.Number, tmpnum);
                        source.RemoveRange(i, 2);
                        i--;
                    }
                    else
                    {
                        errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                        return false;
                    }
                }
            }    // > < >= <=
            for (int i = 0; i < source.Count; i++)
            {
                if (source[i].Type == CalcTokenType.Operator && CheckOperator(CalcOperator.Equ | CalcOperator.Neq, (CalcOperator)source[i].Content) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, -1) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, 1))
                {
                    if (TryGetTokenValue(ref errors, source[i - 1], out double leftnum) && TryGetTokenValue(ref errors, source[i + 1], out double rightnum))
                    {
                        double tmpnum = 0;
                        switch ((CalcOperator)source[i].Content)
                        {
                            case CalcOperator.Equ:
                                tmpnum = leftnum == rightnum ? 1 : 0;
                                break;
                            case CalcOperator.Neq:
                                tmpnum = leftnum != rightnum ? 1 : 0;
                                break;
                            default:
                                throw new Exception();
                        }
                        source[i - 1] = new CalcToken(CalcTokenType.Number, tmpnum);
                        source.RemoveRange(i, 2);
                        i--;
                    }
                    else
                    {
                        errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                        return false;
                    }
                }
            }    // == !=
            for (int i = 0; i < source.Count; i++)
            {
                if (source[i].Type == CalcTokenType.Operator && CheckOperator(CalcOperator.Add | CalcOperator.Or, (CalcOperator)source[i].Content) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, -1) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, 1))
                {
                    if (TryGetTokenValue(ref errors, source[i - 1], out double leftnum) && TryGetTokenValue(ref errors, source[i + 1], out double rightnum))
                    {
                        double tmpnum = 0;
                        switch ((CalcOperator)source[i].Content)
                        {
                            case CalcOperator.Add:
                                tmpnum = leftnum != 0 && rightnum != 0 ? 1 : 0;
                                break;
                            case CalcOperator.Or:
                                tmpnum = leftnum != 0 || rightnum != 0 ? 1 : 0;
                                break;
                            default:
                                throw new Exception();
                        }
                        source[i - 1] = new CalcToken(CalcTokenType.Number, tmpnum);
                        source.RemoveRange(i, 2);
                        i--;
                    }
                    else
                    {
                        errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                        return false;
                    }
                }
            }    // & |
            for (int i = 0; i < source.Count; i++)
            {
                if (source[i].Type == CalcTokenType.Operator && CheckOperator(CalcOperator.If, (CalcOperator)source[i].Content) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, -1) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, 1) && CheckType(ref source, CalcTokenType.Operator, i, 2) && CheckType(ref source, CalcTokenType.Number | CalcTokenType.Expression, i, 3) && CheckOperator(CalcOperator.Witch, (CalcOperator)source[i + 2].Content))
                {
                    if (TryGetTokenValue(ref errors, source[i - 1], out double basic))
                    {
                        double tmpnum = 0;
                        if (basic != 0)
                        {
                            if (TryGetTokenValue(ref errors, source[i + 1], out double leftnum))
                            {
                                tmpnum = leftnum;
                            }
                            else
                            {
                                errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                                return false;
                            }
                        }
                        else
                        {
                            if (TryGetTokenValue(ref errors, source[i + 3], out double rightnum))
                            {
                                tmpnum = rightnum;
                            }
                            else
                            {
                                errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                                return false;
                            }
                        }
                        source[i - 1] = new CalcToken(CalcTokenType.Number, tmpnum);
                        source.RemoveRange(i, 4);
                        i--;
                    }
                    else
                    {
                        errors.Add($"Cannot get the value of token when calculate '{source[i].Content}';");
                        return false;
                    }
                }
            }    // 三元表达式

            if (source.Count == 1 && source[0].Type == CalcTokenType.Number)
            {
                result = (double)source[0].Content;
                return true;
            }
            else
            {
                errors.Add($"Final result after calculate is not a single number. '{string.Join(" ", source)}';");
                return false;
            }
        }
        bool CheckOperator(CalcOperator opt, CalcOperator target)
        {
            return (opt & target) != 0;
        }
        bool CheckType(ref List<CalcToken> source, CalcTokenType type, int index, int offset)
        {
            if (index + offset >= 0 && index + offset < source.Count)
            {
                return ((int)source[index + offset].Type & (int)type) != 0;
            }
            else
            {
                return false;
            }
        }
        bool TryGetTokenValue(ref List<string> errors, CalcToken token, out double result)
        {
            if (token.Type == CalcTokenType.Number)
            {
                result = (double)token.Content;
                return true;
            }
            else if (token.Type == CalcTokenType.Expression)
            {
                List<CalcToken> newtks = (List<CalcToken>)token.Content;
                if (TryCalculateTokens(ref newtks, out double newnum, out List<string> newers))
                {
                    result = newnum;
                    errors.AddRange(newers);
                    return true;
                }
                else
                {
                    result = newnum;
                    errors.AddRange(newers);
                    return false;
                }
            }
            else
            {
                throw new ArgumentOutOfRangeException();
            }
        }

        // 下面是封装好的, 供使用的方法
        public bool TryParseCalcTokens(string expression, out List<CalcToken> result)
        {
            char[] srccs = expression.ToArray();
            int offset = 0;
            return TryParseCalcTokens(ref srccs, ref offset, out result);
        }
        public bool TryCalculateTokens(List<CalcToken> tokens, out double result)
        {
            if (TryCalculateTokens(ref tokens, out result, out List<string> errors))
            {
                return true;
            }
            else
            {
                this.errors.AddRange(errors);
                return false;
            }
        }
        public bool TryCalculate(string expression, out double result)
        {
            result = 0;
            if (!TryParseCalcTokens(expression, out List<CalcToken> tokens))
            {
                return false;
            }
            if (!TryCalculateTokens(tokens, out result))
            {
                return false;
            }
            return true;
        }
        public void PrintErrorText()
        {
            errors.Reverse();
            if (errors.Count != 0)
            {
                Console.WriteLine($"  Most recent exceptions:\n      {string.Join("\n      ", errors)}");
            }
            errors.Clear();
        }
    }
}
