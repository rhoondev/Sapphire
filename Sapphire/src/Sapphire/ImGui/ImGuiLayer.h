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

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();
    private:
        float m_Time = 0.0f;
    };
}
