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
	virtual void draw();
	virtual void	draw(float x, float y);
	virtual void	mouse_button_callback(int window, int action, int mods);
};
#endif
