#pragma once

#define _USE_MATH_DEFINES
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>
#include "bankersrounding.h"

using namespace NCalculator;
using namespace NCalculatorLibExprs;

namespace NCalculatorLib
{
	class NCalc final
	{
	private:
		static std::unordered_map<std::wstring, double> DefaultConstants;
		static std::unordered_map<std::wstring, std::function<double()>*> DefaultVariables;
		static std::unordered_map<std::wstring, std::function<double(std::vector<double>)>*> DefaultFunctions;
		static std::unordered_map<std::wstring, double> Constants;
		static std::unordered_map<std::wstring, std::function<double()>*> Variables;
		static std::unordered_map<std::wstring, std::function<double(std::vector<double>)>*> Functions;

	private:
		class StaticConstructor
		{
		public:
			StaticConstructor();
		};

	private:
		static NCalc::StaticConstructor staticConstructor;


	public:
		static std::unordered_map<std::wstring, double> getDefaultConstants();
		static std::unordered_map<std::wstring, std::function<double()>*> getDefaultVariables();
		static std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>*> getDefaultFunctions();

		static std::unordered_map<std::wstring, double> getConstants();
		static std::unordered_map<std::wstring, std::function<double()>*> getVariables();
		static std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>*> getFunctions();

		static double Go(const std::wstring &expr);

		static double Go(Stream *exprStream);


	private:
		class FunctionDefinition final
		{

		public:
			static double Abs(std::vector<double> &args);


			static double Ceil(std::vector<double> &args);


			static double Floor(std::vector<double> &args);


			static double Min(std::vector<double> &args);


			static double Max(std::vector<double> &args);

			static double Sum(std::vector<double> &args);


			static double Ln(std::vector<double> &args);


			static double Log(std::vector<double> &args);


			static double Log10(std::vector<double> &args);


			static double Pow(std::vector<double> &args);


			static double Sqrt(std::vector<double> &args);


			static double Exp(std::vector<double> &args);


			static double Cbrt(std::vector<double> &args);


			static double Sin(std::vector<double> &args);


			static double Cos(std::vector<double> &args);


			static double Tan(std::vector<double> &args);


			static double Asin(std::vector<double> &args);


			static double Acos(std::vector<double> &args);


			static double Atan(std::vector<double> &args);


			static double Sinh(std::vector<double> &args);


			static double Cosh(std::vector<double> &args);


			static double Tanh(std::vector<double> &args);


			static double Asinh(std::vector<double> &args);


			static double Acosh(std::vector<double> &args);


			static double Atanh(std::vector<double> &args);


			static double Round(std::vector<double> &args);


			static double Sign(std::vector<double> &args);


			static double Truncate(std::vector<double> &args);

			static double Fact(std::vector<double> &args);
		};
	};
}
