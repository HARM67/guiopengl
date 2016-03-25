#ifndef CIMAGE_HPP
# define CIMAGE_HPP
# include "CGraphic.hpp"
# include "CShader.hpp"

class	CImage	
{
private:
	static CImage	singleton;
	GLuint			m_text_co;
	GLuint			m_scr;
	GLuint			m_pos;
	GLuint			m_size;
	GLuint			m_vao;
	GLuint			m_vbo;
	CGraphic		*p_graphic;
	GLuint 			m_shader_programme;
	CImage();
	~CImage();
public:
	static void	draw_Image(t_position pos, t_size size, GLuint img)
	{
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUseProgram (singleton.m_shader_programme);
		glUniform2f(singleton.m_scr, singleton.p_graphic->width / 2.0f, singleton.p_graphic->height / 2.0f);
		glUniform2f(singleton.m_pos, pos.x, pos.y);
		glUniform2f(singleton.m_size, size.width, size.height);
		glBindVertexArray(singleton.m_vao);
		glBindTexture (GL_TEXTURE_2D, img);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
};
#endif
