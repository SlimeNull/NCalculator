# NCalculator
这是一个简单的, 功能较为完善的计算器, 使用递归下降分析表达式语法.

支持:
- [x] 四则运算 + - * /
- [x] 拓展运算 幂(**或^) 求余(%)
- [x] 嵌套计算 可使用任意层级括号进行嵌套
- [x] 关系运算 大于(>) 小于(<) 大于等于(>=) 小于等于(<=) 等于(=或==) 不等于(!=或<>或><)
- [x] 常量变量 可自定义常量与变量
- [x] 函数运算 可调用 Math 中所有数学运算函数, 同时也支持自定义
- [ ] 逻辑运算 支持逻辑 与(&) 或(|) 非(!)
- [x] 表达式编译

## 使用

解析:
```csharp
Expr expr = NCalc.Parse("1+1");
```

解析并计算:
```csharp
Expr expr = NCalc.Parse("1+1");
double value = expr.Eval();
```

计算:
```csharp
NCalc.Eval("1+1");   // returns 2
NCalc.Eval("pi");    // returns 3.141592653589793
NCalc.Eval("2 > 3"); // returns 0 (false)
NCalc.Eval("2 > 1"); // returns 1 (true)
NCalc.Eval("1 > 3 ? 114 : 514");   // returns 514
NCalc.Eval("pow(2, 10)");          // returns 1024
NCalc.Eval("sqrt(4)");             // returns 2
```

带参数计算:
```csharp
NCalcContext context = new NCalcContext();
context.Varialble["my_var"] = () => DateTime.Now.Year;

double value = NCalc.Eval(context, "my_var + 1");
```

编译:
```csharp
Func<double> func = NCalc.Compile("1+1");
```

带上下文编译:
```csharp
NCalcContext context = new NCalcContext();
context.Varialble["my_var"] = () => DateTime.Now.Year;

Func<double> func = NCalc.Compile(context, "my_var + 1");
```

自定义常量:
```csharp
NCalcContext.Default.Constants["x"] = 10;
NCalcContext.Default.Eval("x + 1"); // returns 11
```

自定义变量:
```csharp
double count = 0;
NCalcContext.Default.Variables["count"] = () => count++;
NCalcContext.Default.Eval("count"); // returns 0
NCalcContext.Default.Eval("count"); // returns 1
NCalcContext.Default.Eval("count"); // returns 2
```

自定义函数:
```csharp
NCalcContext.Default.Functions["myfunc"] = (values) => values.Sum();
NCalcContext.Default.Eval("myfunc(1, 2, 3)");    // returns 6
```

## 类型

- Expr 及其子类: 可运算的表达式
- Lexer 词法分析器
- Parser 语法分析器
- Token 词法单元
- NCalc 计算器


