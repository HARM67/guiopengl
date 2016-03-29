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
	FT_Face     	face;
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
	int error;

	GLuint			m_scr;
	GLuint			m_pos;
	GLuint			m_size;
	GLuint			m_color;
	GLuint 			m_shader_programme;

	FT_GlyphSlot	print_char(unsigned int	c, t_position pos, t_color color);
	void			load_char_font(unsigned int c);
public:

	void	print_all_slot();
	static void	load_font(string name, string font_name, unsigned int size)
	{
		CFont	*rt;
		
		map<string, CFont *>::iterator it;
		it = list.find(name);
		if (it != list.end())
			return ;
		rt = new CFont();
		rt->size = size;
		rt->font_name = font_name;
		rt->load();
		list.insert(pair<string, CFont *>(name, rt));
		cout << "J'ai insere " << name << endl;
	};
	static FT_GlyphSlot	put_char(string name, unsigned int c, t_position pos, t_color color)
	{
		map<string, CFont *>::iterator it;
		it = list.find(name);
		if (it == list.end())
			return (0);
		return (it->second->print_char(c, pos, color));
	};
	static FT_GlyphSlot	get_drawsize(string name, unsigned int c)
	{
		map<string, CFont *>::iterator it;
		it = list.find(name);
		if (it == list.end())
			return (0);
		t_font2::iterator it2;
		
		it2 = it->second->char_font.find(c);
		if (it2 == it->second->char_font.end())
		{
			it->second->load_char_font(c);
			it2 = it->second->char_font.find(c);
		}
		return (it2->second->face->glyph);
	};
};
#endif

