# CalculatorPlus
这是一个简单的, 功能较为完善的计算器, 使用递归下降分析表达式语法.

支持:
- [x] 四则运算 + - * /
- [x] 拓展运算 幂(**或^) 求余(%)
- [x] 嵌套计算 可使用任意层级括号进行嵌套
- [x] 关系运算 大于(>) 小于(<) 大于等于(>=) 小于等于(<=) 等于(=或==) 不等于(!=或<>或><)
- [x] 常量变量 可自定义常量与变量
- [x] 函数运算 可调用 Math 中所有数学运算函数, 同时也支持自定义
- [ ] 逻辑运算 支持逻辑 与(&) 或(|) 非(!)

## 使用

计算:
```csharp
NCalc.Go("1+1");   // returns 2
NCalc.Go("pi");    // returns 3.141592653589793
NCalc.Go("2 > 3"); // returns 0 (false)
NCalc.Go("2 > 1"); // returns 1 (true)
NCalc.Go("1 > 3 ? 114 : 514");   // returns 514
NCalc.Go("pow(2, 10)");          // returns 1024
NCalc.Go("sqrt(4)");             // returns 2
```

自定义常量:
```csharp
NCalc.Constants["x"] = 10;
NCalc.Go("x + 1"); // returns 11
```

自定义变量:
```csharp
double count = 0;
NCalc.Variables["count"] = () => count++;
NCalc.Go("count"); // returns 0
NCalc.Go("count"); // returns 1
NCalc.Go("count"); // returns 2
```

自定义函数:
```csharp
NCalc.Functions["myfunc"] = (values) => values.Sum();
NCalc.Go("myfunc(1, 2, 3)");    // returns 6
```

## 类型

- Expr 及其子类: 可运算的表达式
- Lexer 词法分析器
- Parser 语法分析器
- Token 词法单元
- NCalc 计算器


