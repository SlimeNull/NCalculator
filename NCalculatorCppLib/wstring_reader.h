#pragma once
#include <string>

class wstring_reader
{
    private:
    size_t p;
    std::wstring str;

    public:
    wstring_reader();
    wstring_reader(std::wstring str);
    wchar_t peek();
    wchar_t read();
    bool is_end();
};

