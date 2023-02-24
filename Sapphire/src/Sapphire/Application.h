#pragma once

#include "Sapphire/Core.h"
#include "Sapphire/Window.h"
#include "Sapphire/LayerStack.h"
#include "Sapphire/Events/ApplicationEvent.h"

namespace Sapphire
{
    class SAPPHIRE_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        void OnEvent(Event& e);
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
    };

    Application *CreateApplication();
}