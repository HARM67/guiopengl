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
	bool		movable;
	t_size		size;
	static CAui		m_instance;
	vector <CAui*>	content;
	CAui();
	~CAui();
	
public:
	static bool		run;
	t_position	before_click;
	t_position	pos;
	t_position	abs_pos;
	bool		in_move;
	string		name;
	virtual void	draw();
	virtual void	draw(float, float){};
	virtual void	draw_child(float pos_x, float pos_y);
	static t_position	click_down;
	static CAui	*Instance()
	{
		return (&m_instance);
	};
	static CAui	*create_instant()
	{
		return (new CAui);
	};
	void	set_position(float x, float y);
	void	set_size(float width, float height);
	void	add_Elem(CAui *elem);
	CAui	*why(float x, float y);
	virtual void	set_sprite(string){};
	virtual void	mouse_button_callback(int button, int action, int mods);
	void			(*click)(void);
};
#endif
