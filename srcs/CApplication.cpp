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
	CAui			*bt4;

	bt2 = CAui_window::create_window();
	bt2->set_position(0.0f, 0.0f);
	bt2->set_size(180.0f, CGraphic::Instance()->height / 3);
	only->add_Elem(bt2);

	only->add_Elem(CAui_texte::create_texte("Salut"));

	bt3 = CAui_button::create_button();

	bt3->click = insert_window;
	bt2->add_Elem(bt3);

	bt3 = CAui_button::create_button();
	bt3->click = quit;
	bt2->add_Elem(bt3);
}

void	CApplication::init()
{

	t_position	pos;
	pos.x = 250.0f;
	pos.y = 300.0f;
	t_color	color;
	color.red = 1.0f;
	color.alpha = 1.0f;
	CFont::load_font("font1", "/Library/Fonts/Andale Mono.ttf", 250);
	
	insert_window(0);
	while( glfwGetKey(CGraphic::Instance()->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(CGraphic::Instance()->m_window) == 0 &&
			CAui::run)
	{
	pos.x = 250.0f;
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CAui::Instance()->draw();
		CFont::put_char("font1", 'l', pos, color);
		pos.x += 20.0f;
		CFont::put_char("font1", 'L', pos, color);
		pos.x += 20.0f;
		CFont::put_char("font1", '@', pos, color);
		pos.x += 20.0f;
		CFont::put_char("font1", '<', pos, color);
		pos.x += 20.0f;
		glfwSwapBuffers(CGraphic::Instance()->m_window);
		glfwPollEvents();
	}
}
