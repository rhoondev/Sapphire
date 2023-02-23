#pragma once

#include "Sapphire/Window.h"
#include "GLFW/glfw3.h"

namespace Sapphire
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProperties& props);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        inline unsigned int GetWidth() const override { return m_Data.Width; }
        inline unsigned int GetHeight() const override { return m_Data.Height; }

        inline void SetEventCallback(const EventCallbackFunction& callback) override { m_Data.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        bool VSyncEnabled() const override;
    private:
        virtual void Init(const WindowProperties& props);
        virtual void Shutdown();

        GLFWwindow* m_Window;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            bool VSync;
            EventCallbackFunction EventCallback;
        };

        WindowData m_Data;
    };
}