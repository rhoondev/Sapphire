#include "sppch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Sapphire
{
	Application::Application() {}
	Application::~Application() {}

	void Application::Run()
	{
		Sapphire::WindowResizeEvent e(1280, 720);
		SAPPHIRE_TRACE(e);
		
		while (true);
	}
}