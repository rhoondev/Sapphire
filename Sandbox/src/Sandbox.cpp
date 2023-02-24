#include "Sapphire.h"

class Sandbox : public Sapphire::Application
{
public:
	Sandbox()
	{
		PushOverlay(new Sapphire::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Sapphire::Application *Sapphire::CreateApplication()
{
	return new Sandbox();
}