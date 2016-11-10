#ifndef SETUP_H
#define SETUP_H

#include <GLFW/glfw3.h>
#include <GL/glew.h>


class Window
{
	GLFWwindow* m_window;

public:

	Window(int width, int height, char const* title)
	{
		glfwInit();

		glfwWindowHint ( GLFW_RESIZABLE, 1 );
		glfwWindowHint ( GLFW_DOUBLEBUFFER, 1 );
		glfwWindowHint ( GLFW_DEPTH_BITS, 24 );

		glfwWindowHint ( GLFW_CLIENT_API, GLFW_OPENGL_API );

		glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 );
		glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 3 );
		glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
		glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

		m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		glfwMakeContextCurrent(m_window);

		glViewport ( 0, 0, (GLsizei)width, (GLsizei)height );

		glfwSwapInterval(1);

	}

	GLFWwindow const* GetGLFWPtr() const
	{
		return m_window;
	}

	GLFWwindow* GetGLFWPtr()
	{
		return m_window;
	}

	void Initialize()
	{
		glewExperimental = GL_TRUE;

		glewInit();

		glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);

	}

	void Destroy()
	{
		glfwDestroyWindow(m_window);
	}
};



#endif //SETUP_H
