#include "CAui.hpp"

CAui::CAui()
{
	cout << "Je suis un container" << endl;
pos.x = 0;
pos.y = 0;
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
	content.push_back(elem);
}

void	CAui::draw()
{
	int	i;

	i = -1;
	while (++i < content.size())
	{
		content[i]->draw(pos.x, pos.y);
	}
}
