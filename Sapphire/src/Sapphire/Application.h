#pragma once

#include "Core.h"

namespace Sapphire
{
	class SAPPHIRE_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	};

	Application *CreateApplication();
}