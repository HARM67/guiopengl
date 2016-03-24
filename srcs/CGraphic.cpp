#include "CGraphic.hpp"

CGraphic	CGraphic::m_instance=CGraphic();

CGraphic::CGraphic()
{
width = 1024;
height = 768;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(width, height, "Salut", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
}

CGraphic::~CGraphic()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

CGraphic	*CGraphic::Instance()
{
	return (&m_instance);
}
