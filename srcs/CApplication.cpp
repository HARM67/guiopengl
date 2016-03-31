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
void	delete_father(CAui *elem)
{
	elem->erase();
}


void	insert_window(CAui	*elem)
{
	CAui			*only = CAui::Instance();
	CAui			*win;
	CAui			*bt;
	CAui			*ct;
	CAui			*ct2;
	CAui			*bt4;
	CAui			*texte;
	CAui			*textedit;


	win = CAui::create("window");
	win->set_position(100.0f, 100.0f);
	only->add_Elem(win);

	textedit = CAui::create("textedit");
	win->add_Elem(textedit);
/*
	win->add_Elem(CAui_loader::parse_object("tt.cat"));

	ct = CAui::create("h_container");
	win->add_Elem(ct);

	ct2 = CAui::create("v_container");
	ct->add_Elem(ct2);

	bt = CAui::create("button");
	bt->set_size(30.0f, 30.0f);
	bt->click = insert_window;
	ct2->add_Elem(bt);

	bt = CAui::create("button");
	bt->set_size(30.0f, 30.0f);
	bt->click = insert_window;
	ct2->add_Elem(bt);

	ct2 = CAui::create("v_container");
	ct->add_Elem(ct2);

	bt = CAui::create("button");
	bt->set_size(120.0f, 30.0f);
	bt->click = insert_window;
	ct2->add_Elem(bt);

	bt = CAui::create("button");
	bt->set_size(120.0f, 30.0f);
	bt->click = insert_window;
	ct2->add_Elem(bt);

	bt = CAui::create("button");
	bt->click = insert_window;
	win->add_Elem(bt);

	bt = CAui::create("button");
	bt->click = delete_father;
	win->add_Elem(bt);
	*/
}

void	CApplication::init()
{
	CAui			*only = CAui::Instance();
	CAui			*text_fps = CAui::create("text");
	CAui			*nb_CAui = CAui::create("text");
	double time;
	int		fps = 0;


	//CAui_loader	loader;
	//
	insert_window(0);
	time = glfwGetTime();
	while( glfwGetKey(CGraphic::Instance()->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(CGraphic::Instance()->m_window) == 0 &&
			CAui::run)
	{
		if (glfwGetTime() - time >= 1.0f)
		{
			text_fps->set_str(to_string(fps));
			time = glfwGetTime();
			fps = 0;
		}
		else
			fps++;
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CAui::Instance()->set_drawsize();
		CAui::Instance()->draw();
		text_fps->draw(5.0f, 5.0f);
		glfwSwapBuffers(CGraphic::Instance()->m_window);
		glfwPollEvents();
	}
}
