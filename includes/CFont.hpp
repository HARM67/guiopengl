#ifndef CAUI_FONT_HPP
# define CAUI_FONT_HPP

# include <string>
# include <vector>
# include <iostream>
# include <map>
# include "CGraphic.hpp"
# include "CShader.hpp"
# include "s_type.h"
# include <ft2build.h>
# include FT_FREETYPE_H
#define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

using namespace std;
typedef	struct s_letter	t_letter;

struct	s_letter
{
	GLuint			nbr;
	FT_GlyphSlot	slot;
};

class	CFont	
{
private:
	typedef map <string, CFont *>			t_font;
	static t_font							list;
	typedef map <unsigned int, t_letter*>	t_font2;
	t_font2									char_font;

	CFont(){};
	~CFont(){};


	void	load();
	unsigned int	size;
	string			font_name;
	FT_Library  library;
	FT_Face     face;
	int error;

	GLuint			m_scr;
	GLuint			m_pos;
	GLuint			m_size;
	GLuint			m_color;
	GLuint 			m_shader_programme;

	void			print_char(unsigned int	c, t_position pos, t_color color);
	void			load_char_font(unsigned int c);
public:
	static void	load_font(string name, string font_name, unsigned int size)
	{
		CFont	*rt;

		rt = new CFont();
		rt->size = size;
		rt->font_name = font_name;
		rt->load();
		list.insert(pair<string, CFont *>(name, rt));
	};
	static void	put_char(string name, unsigned int c, t_position pos, t_color color)
	{
		map<string, CFont *>::iterator it;
		it = list.find(name);
		if (it == list.end())
			return ;
		it->second->print_char(c, pos, color);
	};
};
#endif

