#include "CAui_window.hpp"

Init_window		CAui_window::not_use;

CAui_window::CAui_window()
{
	sprite	= "images/blanc.bmp";
	pos.x = 0;
	pos.y = 0;
	size.width = 0;
	size.height = 0;
	click = 0;
	movable = 1;
	name = "window";
	CTexture::auto_get(sprite, &size);
	bg_color.red = 0.0f;
	bg_color.green = 0.0f;
	bg_color.blue = 0.0f;
	bg_color.alpha = 0.9f;
	size_mode = 0xf;
}

CAui_window::~CAui_window()
{

}

t_size	CAui_window::draw()
{
	if (!visible)
		return (size);
	CImage::draw_Image(pos, size, CTexture::auto_get(sprite), bg_color);
	return (size);
}

void	CAui_window::set_sprite(string filename)
{
	sprite = filename;
	CTexture::auto_get(sprite, &size);
}

t_size	CAui_window::draw(float x, float y)
{
	t_position		v_pos;
	t_size			child_size;
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
	//child_size = getSize(v_pos.x, v_pos.y);
	//
	/*
	*/CImage::draw_Image(v_pos, draw_size, CTexture::auto_get(sprite), bg_color);
	child_size = draw_child(v_pos.x, v_pos.y);
	return (size);
}

t_size	CAui_window::draw_child(float pos_x, float pos_y)
{
	t_size	rt;
	t_size	tmp;
	int	i;

	i = -1;
	rt.width = 0.0f;
	rt.height = 0.0f;
	while (++i < (int)content.size())
	{
		tmp = content[i]->draw(pos_x, pos_y);
		rt.width = (rt.width > content[i]->size.width) ? rt.width : tmp.width;
		rt.height += tmp.height;
		pos_y += tmp.height;
	}
	return (rt);
}

t_size	CAui_window::set_drawsize()
{
	t_size	tmp;
	int	i;

	i = -1;
	draw_size = size;
	while (++i < (int)content.size())
	{
		tmp = content[i]->set_drawsize();
		if ((size_mode & 0xc) == 0xc)
			draw_size.width = (draw_size.width > content[i]->size.width) ? draw_size.width : tmp.width;
		if ((size_mode & 0x2) == 0x2)
			draw_size.height += tmp.height;
	}
	return (draw_size);
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
	//	father->content.insert(father->content.begin(), tmp);
		father->content.push_back(tmp);
	}
	if (click && !action && in_move)
		click(this);
}

void	CAui_window::cursor_position_callback(int status, double xpos, double ypos)
{

}

CAui	*CAui_window::why(float x, float y)
{
	int	i;

	if (x < pos.x || x > pos.x + draw_size.width || y < pos.y || y > pos.y + draw_size.height)
		return (0);
	i = -1;
	while (++i <  (int)content.size())
	{
		if (content[i]->why(x - pos.x, y - pos.y))
			return (content[i]->why(x - pos.x, y - pos.y));
		y -= content[i]->size.height + content[i]->pos.y;
	}
	return (this);
}
