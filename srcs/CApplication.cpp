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

	bt3 = CAui_button::create_button();

	bt3->click = insert_window;
	bt2->add_Elem(bt3);

	bt3 = CAui_button::create_button();
	bt3->click = quit;
	bt2->add_Elem(bt3);
}

void	CApplication::init()
{
	FT_Library  library;   /* handle to library     */
	FT_Face     face;      /* handle to face object */
	int error;

	error = FT_Init_FreeType( &library );
	//if ( error ) {}
	error = FT_New_Face( library,
			"/Library/Fonts/Arial Black.ttf",
			0,
			&face );
	error = FT_Set_Char_Size(
			face,    /* handle to face object           */
			0,       /* char_width in 1/64th of points  */
			16*64,   /* char_height in 1/64th of points */
			300,     /* horizontal device resolution    */
			300 );   /* vertical device resolution      */

	error = FT_Set_Pixel_Sizes(
			face,   /* handle to face object */
			0,      /* pixel_width           */
			16 );   /* pixel_height          */
	/*
	if ( error == FT_Err_Unknown_File_Format )
	{
		... the font file could be opened and read, but it appears
			... that its font format is unsupported
	}
	else if ( error )
	{
		... another error code means that the font file could not
			... be opened or read, or that it is broken...
	}*/
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
