#include "CApplication.hpp"

void	mouse(GLFWwindow *win, double x, double y)
{
/*
	pos.x = (float)x;
	pos.y = (float)y;
*/}

CApplication::CApplication()
{
	//glfwSetCursorPosCallback(CGraphic::Instance()->m_window, mouse);
}

CApplication::~CApplication()
{
}

void	CApplication::init()
{
	CAui	v_caui;
	v_caui.content.push_back(CAui_button::create_button());
	pos.x = 200.0f;
	pos.y = 100.0f;
	size.width = 200;
	size.height = 400;
	double x, y;;

	CImage	image;
	while( glfwGetKey(CGraphic::Instance()->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(CGraphic::Instance()->m_window) == 0)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetCursorPos(CGraphic::Instance()->m_window, &x, &y);
		pos.x = (float)x;
		pos.y = (float)y;
		image.draw_Image(pos, size, 0);
		glfwPollEvents();
		glfwSwapBuffers(CGraphic::Instance()->m_window);
	}
}
