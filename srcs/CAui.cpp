#include "CAui.hpp"

CAui::list_object		CAui::objects;
CAui					CAui::m_instance;
t_position				CAui::click_down;
bool					CAui::run = 1;

CAui::CAui()
{
	pos.x = 0;
	pos.y = 0;
	size.width = CGraphic::Instance()->width;
	size.height = CGraphic::Instance()->height;
	in_move = 0;
	abs_pos.x = 0;
	abs_pos.y = 0;
	before_click.x = 0;
	before_click.y = 0;
	visible = 1;
	movable = 0;
	name = "program";
	bg_color.red = 1.0f;
	bg_color.green = 1.0f;
	bg_color.blue = 1.0f;
	bg_color.alpha = 1.0f;
	size_mode = 0;
}

CAui::~CAui()
{

}

void	CAui::set_position(float x, float y)
{
	pos.x = x;
	pos.y = y;
}
void	CAui::set_size(float width, float height)
{
	size.width = width;
	size.height = height;
}

void	CAui::add_Elem(CAui *elem)
{
	elem->father = this;
	content.push_back(elem);
}

t_size	CAui::draw()
{
	draw_child(pos.x, pos.y);
	return (size);
}

t_size	CAui::draw(float, float)
{
	return (size);
}

void	CAui::set_str(string n_str)
{
	str = n_str;
}

t_size	CAui::set_drawsize()
{
	int	i;

	i = -1;
	draw_size.width = size.width + pos.x;
	draw_size.height = size.height + pos.y;
	while (++i < (int)content.size())
	{
		content[i]->set_drawsize();
	}
	return (draw_size);
}

t_size	CAui::draw_child(float pos_x, float pos_y)
{
	t_size	rt;
	int	i;

	i = -1;
	rt.width = 0.0f;
	rt.height= 0.0f;
	while (++i < (int)content.size())
	{
		content[i]->draw(pos_x, pos_y);
		rt.width += content[i]->size.width;
		rt.height += content[i]->size.height;
	}
	return (rt);
}

CAui	*CAui::why(float x, float y)
{
	int	i;

	if (x < pos.x || x > pos.x + size.width || y < pos.y || y > pos.y + size.height)
		return (0);
	i = (int)content.size();
	while (--i >=  0)
		if (content[i]->why(x - pos.x, y - pos.y))
			return (content[i]->why(x - pos.x, y - pos.y));
	return (this);
}

void	CAui::mouse_button_callback(int button, int action, int mods)
{
	cout << "Clique sur le fond" << endl;
}

void	CAui::cursor_position_callback(int status, double xpos, double ypos)
{

}
