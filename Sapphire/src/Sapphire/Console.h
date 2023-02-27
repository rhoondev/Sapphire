#pragma once

#include <string>

namespace Sapphire
{
    class Console
    {
    public:
        static void Log(std::string message, ...);
        static void LogWarning(std::string message, ...);
        static void LogError(std::string message, ...);
        static void Assert(bool test, std::string message);
        static void Assert(bool test, std::string success, std::string failure);
    private:
        static std::string GetFormattedTime();
    };
}