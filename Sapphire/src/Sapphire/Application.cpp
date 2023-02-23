#include "sppch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"

namespace Sapphire
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
    }

    Application::~Application() {}
    
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Close));
        
        SP_CORE_TRACE("{0}", e);
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0.2, 0.3, 0.4, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::Close(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}