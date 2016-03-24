#ifndef CIMAGE_HPP
# define CIMAGE_HPP
# include "CGraphic.hpp"

struct	bmp_header
{
	char			signature[2];
	unsigned int	file_size;
	char			reserved[4];
};

class	CImage	
{
	GLuint			m_vs;
	GLuint			m_fs;
	GLuint			m_text_co;
	GLuint			m_scr;
	GLuint			m_pos;
	GLuint			m_size;
	GLuint			m_vao;
	GLuint			m_vbo;
	GLuint			m_img;
	GLuint			m_img2;
	CGraphic		*p_graphic;
	GLuint 			m_shader_programme;
	public:
		CImage();
		~CImage();
	void	draw_Image(t_position pos, t_size size, GLuint img);
};
#endif
