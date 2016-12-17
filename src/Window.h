#ifndef SETUP_H
#define SETUP_H

#include <GLFW/glfw3.h>
#include <GL/glew.h>


class Window
{
	GLFWwindow* m_Window;

public:

	Window(int width, int height, char const* title)
	{
		glfwInit();

		glfwWindowHint ( GLFW_RESIZABLE, GL_FALSE );
		glfwWindowHint ( GLFW_DOUBLEBUFFER, 1 );
		glfwWindowHint ( GLFW_DEPTH_BITS, 24 );

		glfwWindowHint ( GLFW_CLIENT_API, GLFW_OPENGL_API );

		glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 4 );
		glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 1 );
		glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
		glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

		m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		glfwMakeContextCurrent(m_Window);

		glViewport ( 0, 0, (GLsizei)width, (GLsizei)height );

		glfwSwapInterval(1);

	}

	GLFWwindow* const GetGLFWPtr() const
	{
		return m_Window;
	}

	GLFWwindow* GetGLFWPtr()
	{
		return m_Window;
	}

	void Initialize()
	{
		glewExperimental = GL_TRUE;

		glewInit();

		glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GL_TRUE);

	}

	void Destroy()
	{
		glfwDestroyWindow(m_Window);

	}
};



#endif //SETUP_H
