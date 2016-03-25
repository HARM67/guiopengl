#include "CAui_button.hpp"

CAui_button::CAui_button()
{
	sprite	= "images/default_button.png";
	pos.x = 0;
	pos.y = 0;
	size.width = 0;
	size.height = 0;
	click = 0;
	name = "button";
}

CAui_button::~CAui_button()
{

}

void CAui_button::draw()
{
	if (!visible)
		return ;
	CImage::draw_Image(pos, size, CTexture::auto_get(sprite, &size));
}

void	CAui_button::set_sprite(string filename)
{
	sprite = filename;
}

void	CAui_button::draw(float x, float y)
{
	t_position		v_pos;

	v_pos.x = x + pos.x;
	v_pos.y = y + pos.y;
	CImage::draw_Image(v_pos, size, CTexture::auto_get(sprite, &size));
	draw_child(v_pos.x, v_pos.y);
}

void	CAui_button::mouse_button_callback(int button, int action, int mods)
{
	if (click && !action && in_move)
		click(this);
}
