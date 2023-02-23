#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Sapphire
{
    class SAPPHIRE_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();
        void OnEvent(Event& e);
    private:
        bool Close(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    Application *CreateApplication();
}