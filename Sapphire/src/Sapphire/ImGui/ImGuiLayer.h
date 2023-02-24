#pragma once

#include "Sapphire/Layer.h"
#include "Sapphire/Events/ApplicationEvent.h"
#include "Sapphire/Events/MouseEvent.h"
#include "Sapphire/Events/KeyEvent.h"

namespace Sapphire
{
    class SAPPHIRE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);

        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);

        bool OnWindowResizeEvent(WindowResizeEvent& e);

        float m_Time = 0.0f;
    };
}
