#include "sppch.h"
#include "Platform/OpenGL/OpenGLContext.h"
#include "Sapphire/Core.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sapphire
{
	OpenGLContext::OpenGLContext(GLFWwindow* window) : m_Window(window)
	{
		CORE_ASSERT(window, "OpenGLContext created", "OpenGLContext not created (window is null)!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CORE_ASSERT(status, "Initialized Glad", "Failed to initialize Glad!");
		
		Console::Log("Graphics Info:");
		Console::Log(" - Vendor: %s", glGetString(GL_VENDOR));
		Console::Log(" - Renderer: %s", glGetString(GL_RENDERER));
		Console::Log(" - Version: %s", glGetString(GL_VERSION));
		
		CORE_ASSERT_FAILURE(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}