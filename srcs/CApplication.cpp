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

void	quit()
{
	CAui::run = 0;
}

void	CApplication::init()
{
	CAui			*only = CAui::Instance();
	CAui			*bt;
	CAui			*bt2;
	CAui			*bt3;

	only->name = "Window";
	bt = CAui_button::create_button();
	bt->set_sprite("images/lena.bmp");
	bt->set_position(200.0f, 200.0f);
	only->add_Elem(bt);
	
	bt->name = "bt1";
	bt2 = CAui_button::create_button();
	bt2->set_sprite("images/default_button2.png");
	bt->add_Elem(bt2);
	bt2->name = "bt2";
	bt3 = CAui_button::create_button();
	bt3->click = quit;
	bt3->set_sprite("images/default_button1.png");
	bt2->set_position(50.0f, 20.0f);
	bt2->add_Elem(bt3);
	bt3->name = "bt3";
	
	while( glfwGetKey(CGraphic::Instance()->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(CGraphic::Instance()->m_window) == 0 &&
			CAui::run)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		only->draw();
		glfwPollEvents();
		glfwSwapBuffers(CGraphic::Instance()->m_window);
	}
}
