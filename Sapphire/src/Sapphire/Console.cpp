#include "sppch.h"

#include "Sapphire/Console.h"
#include <stdio.h>
#include <ctime>
#include <iomanip>
#include <cstdarg>

namespace Sapphire
{
    void Console::Log(std::string message, ...)
    {
        std::cout << "\x1b[37m" << GetFormattedTime();
        va_list args;
        va_start(args, message);
        vprintf(message.c_str(), args);
        printf("\n");
    }

    void Console::LogWarning(std::string message, ...)
    {
        std::cout << "\x1b[33m" << GetFormattedTime();
        va_list args;
        va_start(args, message);
        vprintf(message.c_str(), args);
        printf("\n");
    }

    void Console::LogError(std::string message, ...)
    {
        std::cout << "\x1b[31m" << GetFormattedTime();
        va_list args;
        va_start(args, message);
        vprintf(message.c_str(), args);
        printf("\n");
    }

    void Console::Assert(bool test, std::string message)
    {
        if (!test)
        {
            std::cout << "\x1b[31m" << GetFormattedTime() << "Assertion failed: " << message << '\n';
        }
    }

    void Console::Assert(bool test, std::string success, std::string failure)
    {
        if (test)
        {
            std::cout << "\x1b[32m" << GetFormattedTime() << "Assertion succeeded: " << success << '\n';
        }
        else
        {
            std::cout << "\x1b[31m" << GetFormattedTime() << "Assertion failed: " << failure << '\n';
        }
    }

    std::string Console::GetFormattedTime()
    {
        time_t currentTime = time(nullptr);
        struct tm* localTime = localtime(&currentTime);

        std::stringstream ss;
        ss << std::put_time(localTime, "[%H:%M:%S] ");
        return ss.str();
    }
}

