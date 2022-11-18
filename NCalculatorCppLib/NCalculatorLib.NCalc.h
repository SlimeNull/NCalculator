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
	class ncalc final
	{
	private:
		static std::unordered_map<std::wstring, double> DefaultConstants;
		static std::unordered_map<std::wstring, std::function<double()>> DefaultVariables;
		static std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>> DefaultFunctions;
		static std::unordered_map<std::wstring, double> Constants;
		static std::unordered_map<std::wstring, std::function<double()>> Variables;
		static std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>> Functions;

	private:
		class StaticConstructor
		{
		public:
			StaticConstructor();
		};

	private:
		static ncalc::StaticConstructor staticConstructor;


	public:
		static std::unordered_map<std::wstring, double> getDefaultConstants();
		static std::unordered_map<std::wstring, std::function<double()>> getDefaultVariables();
		static std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>> getDefaultFunctions();

		static std::unordered_map<std::wstring, double> getConstants();
		static std::unordered_map<std::wstring, std::function<double()>> getVariables();
		static std::unordered_map<std::wstring, std::function<double(const std::vector<double>&)>> getFunctions();

		static double go(const std::wstring &expr);


	private:
		class func_def final
		{

		public:
			static double abs(const std::vector<double> &args);


			static double ceil(const std::vector<double> &args);


			static double floor(const std::vector<double> &args);


			static double min(const std::vector<double> &args);


			static double max(const std::vector<double> &args);

			static double sum(const std::vector<double> &args);


			static double ln(const std::vector<double> &args);


			static double log(const std::vector<double> &args);


			static double log10(const std::vector<double> &args);


			static double pow(const std::vector<double> &args);


			static double sqrt(const std::vector<double> &args);


			static double exp(const std::vector<double> &args);


			static double cbrt(const std::vector<double> &args);


			static double sin(const std::vector<double> &args);


			static double cos(const std::vector<double> &args);


			static double tan(const std::vector<double> &args);


			static double asin(const std::vector<double> &args);


			static double acos(const std::vector<double> &args);


			static double atan(const std::vector<double> &args);


			static double sinh(const std::vector<double> &args);


			static double cosh(const std::vector<double> &args);


			static double tanh(const std::vector<double> &args);


			static double asinh(const std::vector<double> &args);


			static double acosh(const std::vector<double> &args);


			static double atanh(const std::vector<double> &args);


			static double round(const std::vector<double> &args);


			static double sign(const std::vector<double> &args);


			static double truncate(const std::vector<double> &args);

			static double fact(const std::vector<double> &args);
		};
	};
}
