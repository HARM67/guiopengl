#include "CAui_v_container.hpp"

Init_v_container	CAui_v_container::not_use;

CAui_v_container::CAui_v_container()
{
	pos.x = 0;
	pos.y = 0;
	size.width = 0;
	size.height = 0;
	click = 0;
	movable = 1;
	name = "v_container";
	bg_color.red = 0.0f;
	bg_color.green = 0.0f;
	bg_color.blue = 0.0f;
	bg_color.alpha = 0.9f;
	size_mode = 0xf;
}

CAui_v_container::~CAui_v_container()
{

}

t_size	CAui_v_container::draw()
{
	return (draw_size);
}

t_size	CAui_v_container::draw(float x, float y)
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
	child_size = draw_child(v_pos.x, v_pos.y);
	if ((size_mode & 0x2) == 0x2)
		size.height = child_size.height;
	if ((size_mode & 0xc) == 0xc)
		size.width = child_size.width;
	return (draw_size);
}

t_size	CAui_v_container::set_drawsize()
{
	t_size	tmp;
	int	i;

	i = -1;
		draw_size = size;
	if ((size_mode & 0x2) == 0x2)
		draw_size.height = 0.0f;
	while (++i < (int)content.size())
	{
		tmp = content[i]->set_drawsize();
		if ((size_mode & 0xc) == 0xc)
			draw_size.width = (draw_size.width > content[i]->size.width) ? draw_size.width : tmp.width;
		if ((size_mode & 0x2) == 0x2)
			draw_size.height += tmp.height;
	}
	draw_size.width += pos.x;
	draw_size.height += pos.y;
	return (draw_size);
}
t_size	CAui_v_container::draw_child(float pos_x, float pos_y)
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
		rt.height+= tmp.height;
		pos_y += tmp.height;
	}
	return (rt);
}

void	CAui_v_container::mouse_button_callback(int window, int action, int mods)
{

}

void	CAui_v_container::cursor_position_callback(int status, double xpos, double ypos)
{

}

CAui	*CAui_v_container::why(float x, float y)
{
	int	i;

	if (x < pos.x || x > pos.x + size.width || y < pos.y || y > pos.y + size.height)
		return (0);
	i = -1;
	while (++i <  (int)content.size())
	{
		if (content[i]->why(x - pos.x, y - pos.y))
			return (content[i]->why(x - pos.x, y - pos.y));
		y -= content[i]->size.height + content[i]->pos.y;
	}
	return (0);
}
