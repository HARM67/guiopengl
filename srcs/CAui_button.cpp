#include "CAui_button.hpp"

CAui_button::CAui_button()
{
	sprite	= "images/default_button1.png";
	pos.x = 0;
	pos.y = 0;
	size.width = 512;
	size.height = 512;
	click = 0;
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
	double xpos, ypos;

	abs_pos.x = x + pos.x;
	abs_pos.y = y + pos.y;
	glfwGetCursorPos(CGraphic::Instance()->m_window, &xpos, &ypos);
	if (in_move)
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

void	CAui_button::mouse_button_callback(int button, int action, int mods)
{
	if (click)
		click();
}
