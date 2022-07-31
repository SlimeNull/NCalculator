#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2022 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to perform bankers' rounding in C++.
//----------------------------------------------------------------------------------------
#include <cfenv>
#include <cmath>

class BankersRounding
{
public:
	static double round(double value)
	{
		int currentRoundingMode = std::fegetround();
		std::fesetround(FE_TONEAREST);
		double returnValue = std::rint(value);
		std::fesetround(currentRoundingMode);
		return returnValue;
	}
};
