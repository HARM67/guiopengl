#include "CAui_texte.hpp"

CAui_texte::CAui_texte()
{
	font_size = 16;
	font_name = "default_font";
	font = "/Library/Fonts/Arial Black.ttf";
	CFont::load_font(font_name, font, font_size);
	pos.x = 0;
	pos.y = 0;
	size.width = 0;
	size.height = 0;
	click = 0;
	movable = 0;
	name = "texte";
	color.red = 7.0f;
	color.green = 1.0f;
	color.blue = 2.0f;
	color.alpha = 1.0f;
}

CAui_texte::CAui_texte(string n_str)
{
	font_size = 16;
	font_name = "default_font";
	font = "/Library/Fonts/Arial Black.ttf";
	CFont::load_font(font_name, font, font_size);
	pos.x = 0;
	pos.y = 0;
	size.width = 0;
	size.height = 0;
	click = 0;
	movable = 0;
	name = "texte";
	color.red = 1.0f;
	color.green = 0.0f;
	color.blue = 1.0f;
	color.alpha = 1.0f;
	str = n_str;
}

t_size	CAui_texte::draw()
{
	if (!visible)
		return (size);
	//code print
	return (size);
}

t_size	CAui_texte::print_string(t_position v_pos)
{
	int		i;
	FT_GlyphSlot	slot;
	t_size	rt;

	i = -1;
	v_pos.x += 100.0f;
	v_pos.y += 100.0f;
	while (++i < str.size())
	{
		slot = CFont::put_char(font, str[i], v_pos, color);
		v_pos.x += 20.0f;
	}
	return (rt);
}

t_size	CAui_texte::draw(float x, float y)
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
		size.height = child_size.height + 15.0f;
	if ((size_mode & 0xc) == 0xc)
		size.width = child_size.width;
	print_string(v_pos);
	return (size);
}

t_size	CAui_texte::draw_child(float pos_x, float pos_y)
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

void	CAui_texte::mouse_button_callback(int window, int action, int mods)
{

}

void	CAui_texte::cursor_position_callback(int status, double xpos, double ypos)
{

}

CAui	*CAui_texte::why(float x, float y)
{
	int	i;

	if (x < pos.x || x > pos.x + size.width || y < pos.y || y > pos.y + size.height)
		return (0);
	i = -1;
	y -= 15.0f;
	while (++i <  (int)content.size())
	{
		if (content[i]->why(x - pos.x, y - pos.y))
			return (content[i]->why(x - pos.x, y - pos.y));
		y -= content[i]->size.height + content[i]->pos.y;
	}
	return (0);
}
