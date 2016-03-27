#ifndef CAUI_TEXT_HPP
# define CAUI_TEXT_HPP
# include "CAui.hpp"
# include <iostream>
# include "s_type.h"
# include "CFont.hpp"

class CAui_texte : public CAui
{
private:
	string		str;
	string		font;
	string		font_name;
	t_color		color;
	unsigned int	font_size;
	CAui_texte();
	CAui_texte(string n_str);
	~CAui_texte();
public:
	static CAui	*create_texte()
	{
		return (new CAui_texte);
	};
	static CAui	*create_texte(string n_str)
	{
		return (new CAui_texte(n_str));
	};
	t_size			print_string(t_position vpos);
	virtual t_size	draw();
	virtual t_size	draw(float x, float y);
	virtual void	mouse_button_callback(int button, int action, int mods);
	virtual void	cursor_position_callback(int status, double xpos, double ypos);
	t_size			draw_child(float pos_x, float pos_y);
	virtual CAui	*why(float x, float y);
};
#endif
