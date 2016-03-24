#include "CAui_button.hpp"

CAui_button::CAui_button()
{
cout << "Je suis un bouton" << endl;
	sprite	= "images/2007BMP.jpg";
	pos.x = 0;
	pos.y = 0;
	size.width = 512;
	size.height = 512;
}

CAui_button::~CAui_button()
{

}
void CAui_button::draw()
{
	CImage::draw_Image(pos, size, CTexture::auto_get(sprite));
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
	CImage::draw_Image(v_pos, size, CTexture::auto_get(sprite));
}
