#include "Sapphire.h"

class Sandbox : public Sapphire::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Sapphire::Application* Sapphire::CreateApplication()
{
	return new Sandbox();
}