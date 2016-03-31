#include "CAui_textedit.hpp"

Init_textedit	CAui_textedit::not_use;

CAui_textedit::CAui_textedit()
{
	selected_character[0] = 1;
	selected_character[1] = 1;
}

CAui_textedit::~CAui_textedit()
{

}

int		min(int a, int b)
{
	return (a > b ? b : a);
}

int		max(int a, int b)
{
	return (a > b ? a : b);
}

t_size	CAui_textedit::print_string(t_position v_pos)
{
	int				i;
	FT_GlyphSlot	slot;
	t_size			rt;
	t_position		tmp_pos;
	t_color			sel_color;
	t_size			selecte_size;

	int				cursor_temoin;

	sel_color.red = 1.0f;
	sel_color.green= 0.0f;
	sel_color.blue = 0.0f;
	sel_color.alpha = 1.0f;

	i = -1;
	rt.height = CFont::get_size(font_name);
	rt.width = 0.0f;
	tmp_pos = v_pos;
	cursor_temoin = 0;
	while (++i < str.size())
	{
		if (i >= min(selected_character[0], selected_character[1]) && i < max(selected_character[0], selected_character[1]))
		{
			slot = CFont::get_drawsize(font_name, str[i]);
			selecte_size.width = slot->advance.x >> 6;
			selecte_size.height = CFont::get_size(font_name);
			CImage::draw_Image(tmp_pos, selecte_size, CTexture::auto_get("images/blanc.bmp"), sel_color);
			cursor_temoin = 1;
		}
		else if (i == selected_character[0])
		{
			slot = CFont::get_drawsize(font_name, str[i]);
			selecte_size.width = 1.0f;
			selecte_size.height = CFont::get_size(font_name);
			if (((int)(glfwGetTime() * 2)) & 0x1)
				CImage::draw_Image(tmp_pos, selecte_size, CTexture::auto_get("images/blanc.bmp"), sel_color);
			cursor_temoin = 1;
		}
		if (str[i] == '\n')
		{
			v_pos.y += CFont::get_size(font_name);
			rt.height += CFont::get_size(font_name);
			tmp_pos = v_pos;
			continue ;
		}
		slot = CFont::put_char(font_name, str[i], tmp_pos, color);
		rt.width += slot->bitmap.width + slot->bitmap_left;
		tmp_pos.x += slot->advance.x >> 6;
	}
	if (!cursor_temoin)
	{
		selecte_size.width = 1.0f;
		selecte_size.height = CFont::get_size(font_name);
		if (((int)(glfwGetTime() * 2)) & 0x1)
		CImage::draw_Image(tmp_pos, selecte_size, CTexture::auto_get("images/blanc.bmp"), sel_color);
	}
	return (rt);
}

t_size	CAui_textedit::draw(float x, float y)
{
	t_position		v_pos;
	t_size			child_size;

	v_pos.x = x + pos.x;
	v_pos.y = y + pos.y;
	size = print_string(v_pos);
	return (size);
}
/*
void	CAui_textedit:draw_cursor()
	{
		int				i;
		FT_GlyphSlot	slot;

		i = -1;
		draw_size.height = CFont::get_size(font_name);
		draw_size.width = 0.0f;
		while (++i < str.size())
		{
			if (str[i] == '\n')
			{
				draw_size.height += CFont::get_size(font_name);
				continue ;
			}
			if (selected_character[0] == i)
			{
				
			}
			slot = CFont::get_drawsize(font_name, str[i]);
			//draw_size.width += slot->bitmap.width + slot->bitmap_left;
			draw_size.width += slot->advance.x >> 6;
		}
		return (draw_size);
	}
	*/

void	CAui_textedit::mouse_button_callback(int window, int action, int mods)
{
	cout << str[selected_character[0]] << endl;
}

int		check_key(unsigned char *b_key, double *key, int c_key)
{
	if (b_key[c_key] && key[c_key] <= glfwGetTime())
	{
		key[c_key] = glfwGetTime() + TIME_NEXT_KEY;
		return (1);
	}
	return (0);
}

void	CAui_textedit::key_callback(unsigned char *b_key, double *key)
{
	int i;

	i = GLFW_KEY_A;
	while (i <= GLFW_KEY_Z)
	{
		if (check_key(b_key, key, i))
		{
			if (selected_character[0] != selected_character[1])
			{
			str.erase(min(selected_character[0], selected_character[1]), max(selected_character[0], selected_character[1]) - min(selected_character[0], selected_character[1]));
			selected_character[0] = min(selected_character[0], selected_character[1]);
				selected_character[1] = selected_character[0];
			}
			if (b_key[GLFW_KEY_LEFT_SHIFT] || b_key[GLFW_KEY_RIGHT_SHIFT])
				str.insert(str.begin() + selected_character[0], i);
			else
				str.insert(str.begin() + selected_character[0], i + 32);
			selected_character[0]++;
			selected_character[1] = selected_character[0];
		}
		i++;
	}
	if (check_key(b_key, key, GLFW_KEY_SPACE))
	{
		if (selected_character[0] != selected_character[1])
		{
			str.erase(min(selected_character[0], selected_character[1]), max(selected_character[0], selected_character[1]) - min(selected_character[0], selected_character[1]));
			selected_character[0] = min(selected_character[0], selected_character[1]);
			selected_character[1] = selected_character[0];
		}
		str.insert(str.begin() + selected_character[0], ' ');
		selected_character[0]++;
		selected_character[1] = selected_character[0];
	}
	if (check_key(b_key, key, GLFW_KEY_ENTER) || check_key(b_key, key,GLFW_KEY_KP_ENTER))
	{
		if (selected_character[0] != selected_character[1])
		{
			str.erase(min(selected_character[0], selected_character[1]), max(selected_character[0], selected_character[1]) - min(selected_character[0], selected_character[1]));
			selected_character[0] = min(selected_character[0], selected_character[1]);
			selected_character[1] = selected_character[0];
		}
		str.insert(str.begin() + selected_character[0], '\n');
		selected_character[0]++;
		selected_character[1] = selected_character[0];
	}
	if (check_key(b_key, key, GLFW_KEY_RIGHT))
	{
		//selected_character[1] = selected_character[0];
		if (selected_character[1] < str.size())
		{
			selected_character[1]++;
			if (!b_key[GLFW_KEY_LEFT_SHIFT] && !b_key[GLFW_KEY_RIGHT_SHIFT])
				selected_character[0] = selected_character[1];
		}
		key[GLFW_KEY_RIGHT] = glfwGetTime() + TIME_MOVE_KEY;
	}
	if (check_key(b_key, key, GLFW_KEY_LEFT))
	{
		//selected_character[1] = selected_character[0];
		if (selected_character[1] > 0)
		{
			selected_character[1]--;
			if (!b_key[GLFW_KEY_LEFT_SHIFT] && !b_key[GLFW_KEY_RIGHT_SHIFT])
				selected_character[0] = selected_character[1];
		}
		key[GLFW_KEY_LEFT] = glfwGetTime() + TIME_MOVE_KEY;
	}
	if (check_key(b_key, key, GLFW_KEY_PAGE_UP))
	{
		selected_character[1] = 0;
		if (!b_key[GLFW_KEY_LEFT_SHIFT] && !b_key[GLFW_KEY_RIGHT_SHIFT])
			selected_character[0] = selected_character[1];
		key[GLFW_KEY_PAGE_UP] = glfwGetTime() + TIME_MOVE_KEY;
	}
	if (check_key(b_key, key, GLFW_KEY_PAGE_DOWN))
	{
		selected_character[1] = str.size();
		if (!b_key[GLFW_KEY_LEFT_SHIFT] && !b_key[GLFW_KEY_RIGHT_SHIFT])
			selected_character[0] = selected_character[1];
		key[GLFW_KEY_PAGE_DOWN] = glfwGetTime() + TIME_MOVE_KEY;
	}
	if (check_key(b_key, key, GLFW_KEY_DELETE))
	{
		if (selected_character[0] != selected_character[1])
		{
			str.erase(min(selected_character[0], selected_character[1]), max(selected_character[0], selected_character[1]) - min(selected_character[0], selected_character[1]));
			selected_character[0] = min(selected_character[0], selected_character[1]);
			selected_character[1] = selected_character[0];
		}
		else
		{
			str.erase(selected_character[0], 1);
		}
	}
	if (check_key(b_key, key, GLFW_KEY_BACKSPACE))
	{
		if (selected_character[0] != selected_character[1])
		{
			str.erase(min(selected_character[0], selected_character[1]), max(selected_character[0], selected_character[1]) - min(selected_character[0], selected_character[1]));
			selected_character[0] = min(selected_character[0], selected_character[1]);
			selected_character[1] = selected_character[0];
		}
		else if (selected_character[0] > 0)
		{
			str.erase(selected_character[0] - 1, 1);
			selected_character[0]--;
			selected_character[1] = selected_character[0];
		}
		
	}
}

void	CAui_textedit::cursor_position_callback(int status, double xpos, double ypos)
{

}

CAui	*CAui_textedit::why(float x, float y)
{
	int	i;
	FT_GlyphSlot	slot;
	float			pos_x;
	float			pos_y;

	if (x < pos.x || x > pos.x + draw_size.width || y < pos.y || y > pos.y + draw_size.height)
		return (0);
	pos_x = 0.0f;
	pos_y = 0.0f;
	i = -1;
	while (++i < str.size())
	{
		if (str[i] == '\n')
		{
			pos_x = 0.0f;
			pos_y += CFont::get_size(font_name);
			continue ;
		}
		slot = CFont::get_drawsize(font_name, str[i]);
		if (x >= pos_x && x < pos_x + (slot->advance.x >> 6) &&
			y >= pos_y && y < pos_y + CFont::get_size(font_name))
		{
			/*
			selected_character[0] = i;
			selected_character[1] = i;
			*/return (this);
		}
		pos_x += slot->advance.x >> 6;
	}
	return (this);
}
