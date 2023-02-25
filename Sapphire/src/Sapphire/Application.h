#pragma once

#include "Sapphire/Core.h"
#include "Sapphire/Window.h"
#include "Sapphire/LayerStack.h"
#include "Sapphire/Events/ApplicationEvent.h"
#include "Sapphire/ImGui/ImGuiLayer.h"

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

        inline Window& GetWindow() { return *m_Window; }
        inline static Application& Get() { return *s_Instance; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);

        static Application* s_Instance;
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
    };

    Application *CreateApplication();
}