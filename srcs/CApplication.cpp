#include "CApplication.hpp"

void	mouse(GLFWwindow *win, double x, double y)
{

}

CApplication::CApplication()
{

}

CApplication::~CApplication()
{
}

void	CApplication::init()
{
	CAui	*only = CAui::create_instant();
	only->add_Elem(CAui_button::create_button());
	only->add_Elem(CAui_button::create_button());
	only->add_Elem(CAui_button::create_button());

	while( glfwGetKey(CGraphic::Instance()->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(CGraphic::Instance()->m_window) == 0)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		only->draw();
		glfwPollEvents();
		glfwSwapBuffers(CGraphic::Instance()->m_window);
	}
}
