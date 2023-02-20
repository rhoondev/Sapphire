#pragma once

#ifdef SAPPHIRE_PLATFORM_WINDOWS

extern Sapphire::Application *Sapphire::CreateApplication();

int main(int argc, char **argv)
{
	Sapphire::Application *app = Sapphire::CreateApplication();
	app->Run();
	delete app;
}

#endif