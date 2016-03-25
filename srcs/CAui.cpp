#include "CAui.hpp"

CAui			CAui::m_instance;
t_position		CAui::click_down;
bool			CAui::run = 1;

CAui::CAui()
{
	cout << "Je suis un container" << endl;
	pos.x = 0;
	pos.y = 0;
	size.width = CGraphic::Instance()->width;
	size.height = CGraphic::Instance()->height;
	movable	=	1;
	in_move = 0;
	abs_pos.x = 0;
	abs_pos.y = 0;
	before_click.x = 0;
	before_click.y = 0;
	visible = 1;
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
	static int n = 0;
	n++;
//	name = "elem " +  to_string(n);
	content.push_back(elem);
}

void	CAui::draw()
{
	draw_child(pos.x, pos.y);
}

void	CAui::draw_child(float pos_x, float pos_y)
{
	int	i;

	i = -1;
	while (++i < (int)content.size())
	{
		content[i]->draw(pos_x, pos_y);
	}
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
}
