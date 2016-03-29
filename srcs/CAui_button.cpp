#include "CAui_button.hpp"

Init_button		CAui_button::not_use;

CAui_button::CAui_button()
{
	sprite	= "images/blanc.bmp";
	pos.x = 0.0f;
	pos.y = 0.0f;
	size.width = 150.0f;
	size.height = 30.0f;
	click = 0;
	name = "button";
	CTexture::auto_get(sprite);
	bg_color.alpha = 0.25f;
}

CAui_button::~CAui_button()
{

}

t_size	CAui_button::draw()
{
	if (!visible)
		return (size);
	CImage::draw_Image(pos, size, CTexture::auto_get(sprite), bg_color);
	return (size);
}

void	CAui_button::set_sprite(string filename)
{
	sprite = filename;
	CTexture::auto_get(sprite, &size);
}

t_size	CAui_button::draw(float x, float y)
{
	t_position		v_pos;
	t_size			draw_size;
	t_size			rt;

	v_pos.x = x + pos.x + 1.0f;
	v_pos.y = y + pos.y + 1.0f;
	draw_size.width = size.width - 1.0f;
	draw_size.height = size.height - 1.0f;
	CImage::draw_Image(v_pos, draw_size, CTexture::auto_get(sprite), bg_color);
	rt.width = size.width + pos.x;
	rt.height = size.height + pos.y;
	draw_child(v_pos.x, v_pos.y);
	return (rt);
}

void	CAui_button::mouse_button_callback(int button, int action, int mods)
{
	if (click && !action && in_move)
		click(this);
}

void	CAui_button::cursor_position_callback(int status, double xpos, double ypos)
{
	if (status)
		bg_color.alpha = 0.4f;
	else
		bg_color.alpha = 0.25;
}
