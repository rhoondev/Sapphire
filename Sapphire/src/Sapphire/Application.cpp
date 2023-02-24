#include "sppch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "glad/glad.h"

namespace Sapphire
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
    }

    Application::~Application() {}

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }
    
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(OnWindowResize));
        
        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);

            if (e.Handled)
            {
                break;
            }
        }

        SP_CORE_TRACE("{0}", e);
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0.2, 0.3, 0.4, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }
            
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        m_Minimized = e.GetWidth() == 0 || e.GetHeight() == 0;
        return false;
    }
}