#include "sppch.h"
#include "Sapphire/Application.h"
#include "Sapphire/Events/ApplicationEvent.h"
#include "Sapphire/Input.h"
#include "glad/glad.h"

namespace Sapphire
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        SP_CORE_ASSERT(!s_Instance, "Application already created!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application() {}

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }
    
    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(Application::OnWindowResize));
        
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
            
            if (Input::IsKeyPressed(KeyCode::Space))
            {
                glClearColor(0, 0, 0, 1);
            }
            else
            {
                glClearColor(0.16, 0.16, 0.16, 1);
            }

            glClear(GL_COLOR_BUFFER_BIT);
            
            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();

            for (Layer* layer : m_LayerStack)
            {
                layer->OnImGuiRender();
            }

            m_ImGuiLayer->End();
            
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