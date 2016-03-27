#ifndef CAUI_HPP
# define CAUI_HPP
# include "CGraphic.hpp"
# include <iostream>
# include <vector>
# include "s_type.h"

using namespace std;

class	CAui
{
protected:
	bool		visible;
	static CAui		m_instance;
	CAui();
	~CAui();
	
public:
	t_size		size;
	unsigned char	size_mode;
	t_color			bg_color;
	vector <CAui*>	content;
	CAui		*father;
	bool		movable;
	static bool		run;
	t_position	before_click;
	t_position	pos;
	t_position	abs_pos;
	bool		in_move;
	string		name;
	virtual t_size	draw();
	virtual t_size	draw(float, float);
	virtual t_size	draw_child(float pos_x, float pos_y);
	static t_position	click_down;
	static CAui	*Instance()
	{
		return (&m_instance);
	};
	/*static CAui	*create_instant()
	{
		return (new CAui);
	};*/
	void	set_position(float x, float y);
	void	set_size(float width, float height);
	void	add_Elem(CAui *elem);
	virtual CAui	*why(float x, float y);
	virtual void	set_sprite(string){};
	virtual void	mouse_button_callback(int button, int action, int mods);
	virtual void	cursor_position_callback(int status, double xpos, double ypos);
	void			(*click)(CAui	*);
};
#endif
