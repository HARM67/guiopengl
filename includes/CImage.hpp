#ifndef CIMAGE_HPP
# define CIMAGE_HPP
# include "CGraphic.hpp"
# include "CShader.hpp"
# include "s_type.h"

class	CImage	
{
private:
	static CImage	singleton;
	GLuint			m_scr;
	GLuint			m_pos;
	GLuint			m_size;
	GLuint			m_color;
	CGraphic		*p_graphic;
	GLuint 			m_shader_programme;
	CImage();
	~CImage();
public:
	static void	draw_Image(t_position pos, t_size size, GLuint img, t_color color)
	{
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUseProgram (singleton.m_shader_programme);
		glUniform2f(singleton.m_scr, singleton.p_graphic->width / 2.0f, singleton.p_graphic->height / 2.0f);
		glUniform2f(singleton.m_pos, pos.x, pos.y);
		glUniform2f(singleton.m_size, size.width, size.height);
		glUniform4f(singleton.m_color, color.red, color.green, color.blue, color.alpha);
		glBindVertexArray(CGraphic::Instance()->get_vao());
		glBindTexture (GL_TEXTURE_2D, img);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};
#endif
