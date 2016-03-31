#include "CAui_texte.hpp"

Init_texte	CAui_texte::not_use;

CAui_texte::CAui_texte()
{
	font_size = 16;
	font_name = "Arial Narrow 16";
	font = "fonts/Arial Narrow.ttf";
	CFont::load_font(font_name, font, font_size);
	pos.x = 0;
	pos.y = 0;
	size.width = 0;
	size.height = 0;
	click = 0;
	movable = 0;
	name = "text";
	color.red = 1.0f;
	color.green = 1.0f;
	color.blue = 1.0f;
	color.alpha = 1.0f;
	str = "zone de texte";
}

CAui_texte::CAui_texte(string n_str)
{
	str = n_str;
	font_size = 16;
	font_name = "Arial Narrow 16";
	font = "fonts/Arial Narrow.ttf";
	CFont::load_font(font_name, font, font_size);
	pos.x = 0;
	pos.y = 0;
	size.width = 0;
	size.height = 0;
	click = 0;
	movable = 0;
	name = "text";
	color.red = 1.0f;
	color.green = 1.0f;
	color.blue = 1.0f;
	color.alpha = 1.0f;
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
	int				i;
	FT_GlyphSlot	slot;
	t_size			rt;
	t_position		tmp_pos;

	i = -1;
	rt.height = CFont::get_size(font_name);
	rt.width = 0.0f;
	tmp_pos = v_pos;
	while (++i < str.size())
	{
		if (str[i] == '\n')
		{
			v_pos.y += CFont::get_size(font_name);
			rt.height += CFont::get_size(font_name);
			tmp_pos = v_pos;
			continue ;
		}
		slot = CFont::put_char(font_name, str[i], tmp_pos, color);
		//rt.height = (rt.height > sl)
		rt.width += slot->bitmap.width + slot->bitmap_left;
		tmp_pos.x += slot->advance.x >> 6;
	}
	return (rt);
}

t_size	CAui_texte::draw(float x, float y)
{
	t_position		v_pos;
	t_size			child_size;

	v_pos.x = x + pos.x;
	v_pos.y = y + pos.y;
	size = print_string(v_pos);
	return (size);
}

t_size	CAui_texte::set_drawsize()
{
	int				i;
	FT_GlyphSlot	slot;
	float			current_width;

	i = -1;
	draw_size.height = CFont::get_size(font_name);
	draw_size.width = 0.0f;
	while (++i < str.size())
	{
		if (str[i] == '\n')
		{
			draw_size.height += CFont::get_size(font_name);
			draw_size.width = (draw_size.width > current_width) ? draw_size.width : current_width;
			current_width = 0.0f;
			continue ;
		}
		slot = CFont::get_drawsize(font_name, str[i]);
		//draw_size.width += slot->bitmap.width + slot->bitmap_left;
		current_width += slot->advance.x >> 6;
	}
	draw_size.width = (draw_size.width > current_width) ? draw_size.width : current_width;
	return (draw_size);
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

	if (x < pos.x || x > pos.x + draw_size.width || y < pos.y || y > pos.y + draw_size.height)
		return (0);
	i = -1;
	y -= 15.0f;
	while (++i <  (int)content.size())
	{
		if (content[i]->why(x - pos.x, y - pos.y))
			return (content[i]->why(x - pos.x, y - pos.y));
		y -= content[i]->draw_size.height + content[i]->pos.y;
	}
	return (0);
}
