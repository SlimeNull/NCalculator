#pragma once

#include <string>
#include <exception>

class ArgumentOutOfRangeException : public std::exception
{
private:
    std::string msg;

public:
    ArgumentOutOfRangeException(const std::string& message = "") : msg(message)
    {
    }

    const char * what() const noexcept
    {
        return msg.c_str();
    }
};
