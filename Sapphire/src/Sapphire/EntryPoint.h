#pragma once

#include "Log.h"

#ifdef SP_PLATFORM_WINDOWS

extern Sapphire::Application *Sapphire::CreateApplication();

int main(int argc, char **argv)
{
    Sapphire::Log::Init();
    SP_CORE_INFO("Welcome to Sapphire Engine!");

    Sapphire::Application *app = Sapphire::CreateApplication();
    app->Run();
    delete app;
}

#endif