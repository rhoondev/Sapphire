#include "sppch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "Sapphire/Application.h"


#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM

namespace Sapphire
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

    void ImGuiLayer::OnAttach()
    {
        // IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        /*io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;*/

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;

        ImGui::StyleColorsDark();

        /*ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }*/

        // GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        // ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        // ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Window& window = Application::Get().GetWindow();
        io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = time - m_Time;
        m_Time = time;
        
        ImGui_ImplOpenGL3_NewFrame();
        // ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();

        /*int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.2, 0.3, 0.4, 1);
        glClear(GL_COLOR_BUFFER_BIT);*/

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnWindowResizeEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();

        if (keycode > 0 && keycode < 0x10000)
        {
            io.AddInputCharacter((unsigned int)keycode);
        }

        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1, 1);
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
        
        return false;
    }
}