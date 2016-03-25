#include "CApplication.hpp"

void	mouse(GLFWwindow *win, double x, double y)
{

}

void	quit(CAui	*elem)
{
	CAui::run = 0;
}

void	resize(CAui	*elem)
{
//	vector <string, CAui *>
//	CAui			*only = CAui::Instance();

}

void	insert_window(CAui	*elem)
{
	CAui			*only = CAui::Instance();
	CAui			*bt;
	CAui			*bt2;
	CAui			*bt3;

	only->name = "Ground";

	bt = CAui_window::create_window();
	bt->set_position(50.0f, 50.0f);
	only->add_Elem(bt);
	
	bt2 = CAui_button::create_button();
	bt2->set_position(50.0f, 20.0f);
	bt2->click = insert_window;
	bt->add_Elem(bt2);

	bt2 = CAui_button::create_button();
	bt2->set_position(150.0f, 200.0f);
	bt2->click = insert_window;
	bt->add_Elem(bt2);

	bt3 = CAui_button::create_button();
	bt3->set_position(250.0f, 400.0f);
	bt3->click = quit;
	bt->add_Elem(bt3);
}

void	CApplication::init()
{
	insert_window(0);
	
	while( glfwGetKey(CGraphic::Instance()->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(CGraphic::Instance()->m_window) == 0 &&
			CAui::run)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CAui::Instance()->draw();
		glfwPollEvents();
		glfwSwapBuffers(CGraphic::Instance()->m_window);
	}
}
