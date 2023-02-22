#pragma once

#include "Log.h"

#ifdef SAPPHIRE_PLATFORM_WINDOWS

extern Sapphire::Application *Sapphire::CreateApplication();

int main(int argc, char **argv)
{
	Sapphire::Log::Init();
	SAPPHIRE_CORE_INFO("Welcome to Sapphire Engine!");
	SAPPHIRE_CORE_WARN("This is a warning.");

	Sapphire::Application *app = Sapphire::CreateApplication();
	app->Run();
	delete app;
}

#endif