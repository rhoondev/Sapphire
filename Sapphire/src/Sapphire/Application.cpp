#include "sppch.h"
#include "Sapphire/Application.h"
#include "Sapphire/Events/ApplicationEvent.h"

#include <glad/glad.h>

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Sapphire
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        CORE_ASSERT(!s_Instance, "Application initialized", "Application already created!");
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);

        float triangleVertices[3 * 7] =
        {
            -0.25f, -0.25f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
             0.25f, -0.25f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
             0.0f,   0.25f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
        };

        BufferLayout triangleLayout =
        {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        unsigned int triangleIndices[3] = { 0, 1, 2 };

        std::shared_ptr<VertexBuffer> triangleVertexBuffer;
        triangleVertexBuffer.reset(new OpenGLVertexBuffer(triangleVertices, sizeof(triangleVertices)));
        triangleVertexBuffer->SetLayout(triangleLayout);

        std::shared_ptr<IndexBuffer> triangleIndexBuffer;
        triangleIndexBuffer.reset(new OpenGLIndexBuffer(triangleIndices, 3));

        m_TriangleVertexArray.reset(new OpenGLVertexArray());
        m_TriangleVertexArray->AddVertexBuffer(triangleVertexBuffer);
        m_TriangleVertexArray->SetIndexBuffer(triangleIndexBuffer);

        std::string triangleVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string triangleFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";

        m_TriangleShader.reset(new OpenGLShader(triangleVertexSrc, triangleFragmentSrc));

        float squareVertices[4 * 3] =
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        BufferLayout squareLayout =
        {
            { ShaderDataType::Float3, "a_Position" }
        };

        unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

        std::shared_ptr<VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(new OpenGLVertexBuffer(squareVertices, sizeof(squareVertices)));
        squareVertexBuffer->SetLayout(squareLayout);

        std::shared_ptr<IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(new OpenGLIndexBuffer(squareIndices, 6));

        m_SquareVertexArray.reset(new OpenGLVertexArray());
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        std::string squareVertexSrc = R"(
            #version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string squareFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0f);
            }
        )";

        m_SquareShader.reset(new OpenGLShader(squareVertexSrc, squareFragmentSrc));
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

        Console::Log(e.ToString());
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_SquareShader->Bind();
            m_SquareVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_SquareVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

            m_TriangleShader->Bind();
            m_TriangleVertexArray->Bind();
            glDrawElements(GL_TRIANGLES, m_TriangleVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
            
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