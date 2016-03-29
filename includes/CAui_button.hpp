#ifndef CAUI_BUTTON_HPP
# define CAUI_BUTTON_HPP
#include "CAui.hpp"
#include "CImage.hpp"
#include "CTexture.hpp"


typedef struct Init_button	t_Init_button;
//class	CAui_button;

class	CAui_button : public CAui
{
private:
	static t_Init_button	not_use;
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

struct Init_button
{
	Init_button()
	{
		CAui::objects.insert(pair<string, CAui *(*)()>("button", &CAui_button::create_button));
	}
};
#endif
