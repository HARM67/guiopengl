#ifndef CAUI_TEXT_HPP
# define CAUI_TEXT_HPP
# include "CAui.hpp"
# include <iostream>
# include "s_type.h"
# include "CFont.hpp"

typedef struct Init_texte t_Init_texte;

class CAui_texte : public CAui
{
protected:
	CAui_texte();
	CAui_texte(string n_str);
	~CAui_texte(){};
	string		font;
	string		font_name;
	t_color		color;
	unsigned int	font_size;
private:
	static t_Init_texte		not_use;
public:
	static CAui	*create_texte()
	{
		return (new CAui_texte);
	};
	static CAui	*create_texte(string n_str)
	{
		return (new CAui_texte(n_str));
	};
	virtual t_size			print_string(t_position vpos);
	virtual t_size	draw();
	virtual t_size	draw(float x, float y);
	virtual void	mouse_button_callback(int button, int action, int mods);
	virtual void	cursor_position_callback(int status, double xpos, double ypos);
	t_size			draw_child(float pos_x, float pos_y);
	virtual CAui	*why(float x, float y);
	virtual t_size	set_drawsize();
	virtual void	set_font(string ft_name, string ft, unsigned int size);
};

struct	Init_texte
{
	Init_texte()
	{
		CAui::objects.insert(pair<string, CAui *(*)()>("text", &CAui_texte::create_texte));
	}
};
#endif
