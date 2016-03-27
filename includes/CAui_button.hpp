#ifndef CAUI_BUTTON_HPP
# define CAUI_BUTTON_HPP
#include "CAui.hpp"
#include "CImage.hpp"
#include "CTexture.hpp"

class	CAui_button : public CAui
{
private:
	string	sprite;
	CAui_button();
	~CAui_button();
public:
	static CAui	*create_button()
	{
		return (new CAui_button);
	};
	void	set_sprite(string filename);
	virtual t_size	draw();
	virtual t_size	draw(float x, float y);
	virtual void	mouse_button_callback(int button, int action, int mods);
	virtual void	cursor_position_callback(int status, double xpos, double ypos);
};
#endif
