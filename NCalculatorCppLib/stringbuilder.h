#pragma once

//----------------------------------------------------------------------------------------
//	Copyright © 2004 - 2022 Tangible Software Solutions, Inc.
//	This class can be used by anyone provided that the copyright notice remains intact.
//
//	This class is used to replace the .NET StringBuilder in C++.
//----------------------------------------------------------------------------------------
#include <string>
#include <sstream>

class StringBuilder
{
private:
	std::wstring privateString;

public:
	StringBuilder()
	{
	}

	StringBuilder(const std::wstring &initialString)
	{
		privateString = initialString;
	}

	StringBuilder(std::size_t capacity)
	{
		ensureCapacity(capacity);
	}

	StringBuilder(const std::wstring &initialString, std::size_t capacity)
	{
		privateString = initialString;
		ensureCapacity(capacity);
	}

	wchar_t operator [](std::size_t index)
	{
		return privateString[index];
	}

	StringBuilder *append(const std::wstring &toAppend)
	{
		privateString += toAppend;
		return this;
	}

	template<typename T>
	StringBuilder *append(const T &toAppend)
	{
		privateString += toString(toAppend);
		return this;
	}

	StringBuilder *appendLine()
	{
		privateString += L"\r\n";
		return this;
	}

	StringBuilder *appendLine(const std::wstring &toAppend)
	{
		privateString += toAppend + L"\r\n";
		return this;
	}

	StringBuilder *insert(std::size_t position, const std::wstring &toInsert)
	{
		privateString.insert(position, toInsert);
		return this;
	}

	template<typename T>
	StringBuilder *insert(std::size_t position, const T &toInsert)
	{
		privateString.insert(position, toString(toInsert));
		return this;
	}

	std::wstring toString()
	{
		return privateString;
	}

	std::wstring toString(std::size_t start, std::size_t length)
	{
		return privateString.substr(start, length);
	}

	std::size_t length()
	{
		return privateString.length();
	}

	void setLength(std::size_t newLength)
	{
		privateString.resize(newLength);
	}

	std::size_t capacity()
	{
		return privateString.capacity();
	}

	void ensureCapacity(std::size_t minimumCapacity)
	{
		privateString.reserve(minimumCapacity);
	}

	std::size_t maxCapacity()
	{
		return privateString.max_size();
	}

	void clear()
	{
		privateString.clear();
	}

	StringBuilder *remove(std::size_t start, std::size_t length)
	{
		privateString.erase(start, length);
		return this;
	}

	StringBuilder *replace(const std::wstring &oldString, const std::wstring &newString)
	{
		std::size_t pos = 0;
		while ((pos = privateString.find(oldString, pos)) != std::wstring::npos)
		{
			privateString.replace(pos, oldString.length(), newString);
			pos += newString.length();
		}
		return this;
	}

private:
	template<typename T>
	static std::wstring toString(const T &subject)
	{
		std::wostringstream ss;
		ss << subject;
		return ss.str();
	}
};
