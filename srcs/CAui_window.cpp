#include "CAui_window.hpp"

CAui_window::CAui_window()
{
	sprite	= "images/default_window.png";
	pos.x = 0;
	pos.y = 0;
	size.width = 0;
	size.height = 0;
	click = 0;
	movable = 1;
	name = "window";
}

CAui_window::~CAui_window()
{

}

void CAui_window::draw()
{
	if (!visible)
		return ;
	CImage::draw_Image(pos, size, CTexture::auto_get(sprite, &size));
}

void	CAui_window::set_sprite(string filename)
{
	sprite = filename;
}

void	CAui_window::draw(float x, float y)
{
	t_position		v_pos;
	double xpos, ypos;

	glfwGetCursorPos(CGraphic::Instance()->m_window, &xpos, &ypos);
	if (in_move && movable)
	{
		pos.x += (float)xpos - CAui::click_down.x;
		pos.y += (float)ypos - CAui::click_down.y;
		CAui::click_down.x = (float)xpos;
		CAui::click_down.y = (float)ypos;
	}
	v_pos.x = x + pos.x;
	v_pos.y = y + pos.y;
	CImage::draw_Image(v_pos, size, CTexture::auto_get(sprite, &size));
	draw_child(v_pos.x, v_pos.y);
}

void	CAui_window::mouse_button_callback(int window, int action, int mods)
{
	int	i;
	int j;
	CAui	*tmp;

	if (action == 1)
	{
		j = father->content.size();
		i = -1;
		while (++i < j)
		{
			if (this == father->content[i])
				break ;
		}
		if (i == -1)
			return ;
		tmp = father->content[i];
		father->content.erase(father->content.begin() + i);
		father->content.push_back(tmp);
	}
	if (click && !action && in_move)
		click(this);
}
