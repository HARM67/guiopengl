#ifndef CAUI_HPP
# define CAUI_HPP
# include "CGraphic.hpp"
# include <iostream>
# include <vector>
# include <map>
# include <string>
# include "s_type.h"


class	CAui;

using namespace std;

class	CAui
{
protected:
	bool		visible;
	static CAui		m_instance;
	CAui();
	~CAui();
	string		str;
	
public:
	bool					is_focus;
	typedef vector<CAui *> list_child;
	typedef	map<string, CAui *(*)()>	list_object;
	static list_object				objects;
	list_child	content;
	t_size		size;
	t_size		draw_size;
	unsigned char	size_mode;
	t_color			bg_color;
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
	static void	record_object(string name, CAui *(*f)())
	{
		objects.insert(pair<string, CAui *(*)()>(name, f));
	}
	static CAui	*Instance()
	{
		return (&m_instance);
	};
	static CAui	*create(string name)
	{
		list_object::iterator	it;
		it = objects.find(name);
		return (it->second());
	};
	void	set_position(float x, float y);
	void	set_size(float width, float height);
	void	add_Elem(CAui *elem);
	virtual CAui	*why(float x, float y);
	virtual void	set_sprite(string){};
	virtual void	mouse_button_callback(int button, int action, int mods);
	virtual void	cursor_position_callback(int status, double xpos, double ypos);
	void			(*click)(CAui	*);
	virtual t_size	set_drawsize();

	virtual void key_callback(unsigned char *b_key, double *key){};
	void			set_str(string n_str);
	void			erase();
	virtual void	set_font(string ft_name, string ft, unsigned int size){};
};

#endif
