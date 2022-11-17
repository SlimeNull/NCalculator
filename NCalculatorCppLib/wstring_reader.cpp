#include "wstring_reader.h"

wstring_reader::wstring_reader()
{
    str = L"";
}

wstring_reader::wstring_reader(std::wstring wstr)
{
    str = wstr;
}

wchar_t wstring_reader::peek()
{
    return str[p];
}

wchar_t wstring_reader::read()
{
    return str[p++];
}

bool wstring_reader::is_end()
{
    return p >= str.size();
}
