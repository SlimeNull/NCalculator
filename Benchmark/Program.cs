// See https://aka.ms/new-console-template for more information
using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Running;
using NCalculatorLib;
using NCalculatorLib.Exprs;

Console.WriteLine("Hello, World!");

BenchmarkRunner.Run<PerformanceTest>();

public class PerformanceTest
{
    public static NCalcExpr Expression2Test =
        NCalc.Parse("(2*sin(3*pi/4)+cos(5*pi/6))/(sqrt(25)+3*2)+log(e^2)+max(4,7)-min(2,8)+abs(-10)+ceil(3.5)+floor(4.9)-round(2.3)+atan(1)*acos(-1)+((2^3)*4-5*6)/(7+8*9)-sqrt(10+11)-12/13*14+(15-16)/17*18^2+19%3+20*21-22/23+24*25-26/27+28*29-30/31+32*33-34/35+36*37-38/39+40*41-42/43+44*45-46/47+48*49-50/51+52*53-54/55+56*57-58/59+60*61-62/63+64*65-66/67+68*69-70/71+72*73-74/75+76*77-78/79+80*81-82/83+84*85-86/87+88*89-90/91+92*93-94/95+96*97-98/99+100");

    public static Func<double> CompiledExpression2Test =
        Expression2Test.Compile();



    [Benchmark]
    public double CompileEval()
    {
        return CompiledExpression2Test.Invoke();
    }

    [Benchmark]
    public double Eval()
    {
        return Expression2Test.Eval();
    }
}