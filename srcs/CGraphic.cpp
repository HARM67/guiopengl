#include "CGraphic.hpp"

CGraphic	CGraphic::m_instance=CGraphic();

CGraphic::CGraphic()
{
	width = 2400;
	height = 1200;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(width, height, "<--gui_Opengl-->", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
	glClearColor(0.12f, 0.150f, 0.25f, 0.0f);
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
