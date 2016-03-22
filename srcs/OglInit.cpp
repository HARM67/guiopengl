#include "OglInit.hpp"

OglInit::OglInit()
{
	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
	glfwWindowHint(GL_RED_BITS, 100);
	glfwWindowHint(GL_GREEN_BITS, 100);
	glfwWindowHint(GL_BLUE_BITS, 100);
	window = glfwCreateWindow(640, 480, "Titre", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetWindowPos(window, 100, 100);
	//glfwSetWindowCloseCallback(window, close());
}

OglInit::~OglInit()
{
	close();
}

void	OglInit::render()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

GLFWwindowclosefun	OglInit::close()
{
	glfwDestroyWindow(window);
	return (0);
}
	
