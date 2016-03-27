#ifndef CAUI_WINDOW_HPP
#define CAUI_WINDOW_HPP
#include "CAui.hpp"
#include "CImage.hpp"
#include "CTexture.hpp"

class	CAui_window : public CAui
{
private:
	string	sprite;
	CAui_window();
	~CAui_window();
public:
	static CAui	*create_window()
	{
		return (new CAui_window);
	};
	void	set_sprite(string filename);
	virtual t_size	draw();
	virtual t_size	draw(float x, float y);
	virtual t_size	draw_child(float pos_x, float pos_y);
	virtual void	mouse_button_callback(int window, int action, int mods);
	virtual void	cursor_position_callback(int status, double xpos, double ypos);
	virtual CAui	*why(float x, float y);
};
#endif
