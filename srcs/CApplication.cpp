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
	FT_Library  library; 
	FT_Face     face;   
	int error;
	int	glyph_index;
	GLuint	letter_A;

	error = FT_Init_FreeType( &library );
	error = FT_New_Face( library,
			"/Library/Fonts/Arial Black.ttf",
			0,
			&face );
/*	error = FT_Set_Char_Size(
			face,
			0,  
			48*64, 
			600,  
			600); 
*/
	error = FT_Set_Pixel_Sizes(
			face,
			0,   
			500);

	glyph_index = FT_Get_Char_Index( face, '@');

	error = FT_Load_Glyph(
			face,        
			glyph_index,  
			FT_LOAD_DEFAULT); 

	error = FT_Render_Glyph( face->glyph,
			FT_RENDER_MODE_NORMAL); 
	FT_GlyphSlot  slot = face->glyph;

	glActiveTexture (GL_TEXTURE0);
	glGenTextures (1, &letter_A);
	glBindTexture (GL_TEXTURE_2D, letter_A);
	cout << "W : " << slot->bitmap.width << " H : " << slot->bitmap.rows << endl;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D (
		GL_TEXTURE_2D,
		0,
		GL_RED,
		slot->bitmap.width,
		slot->bitmap.rows,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		slot->bitmap.buffer
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLuint m_shader_programme = CShader::create("CTexte_shader", "./shaders/texte_vs.glsl", "./shaders/texte_fs.glsl");
	
	GLuint m_scr = glGetUniformLocation(m_shader_programme, "scr");
	GLuint m_pos = glGetUniformLocation(m_shader_programme, "pos");
	GLuint m_size = glGetUniformLocation(m_shader_programme, "size");
	GLuint m_color = glGetUniformLocation(m_shader_programme, "in_color");
	insert_window(0);
	while( glfwGetKey(CGraphic::Instance()->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(CGraphic::Instance()->m_window) == 0 &&
			CAui::run)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		CAui::Instance()->draw();
		glBindTexture (GL_TEXTURE_2D, letter_A);
		glUseProgram (m_shader_programme);
		glUniform2f(m_scr, CGraphic::Instance()->width / 2.0f, CGraphic::Instance()->height / 2.0f);
		glUniform2f(m_pos, 100.0f, 100.0f);
		glUniform2f(m_size, 500.0f, 500.0f);
		glUniform4f(m_color, 1, 1, 1, 1);
		glDrawArrays(GL_TRIANGLES, 0, 6);



		glfwSwapBuffers(CGraphic::Instance()->m_window);
		glfwPollEvents();
	}
}
