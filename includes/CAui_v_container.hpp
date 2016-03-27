#ifndef CAUI_V_CONTAINER_HOO
# define CAUI_V_CONTAINER_HOO

#include "CAui.hpp"

class	CAui_v_container : public CAui
{
private:
	CAui_v_container();
	~CAui_v_container();
public:
	static CAui	*create_v_container()
	{
		return (new CAui_v_container);
	};
	virtual t_size	draw();
	virtual t_size	draw(float x, float y);
	virtual t_size	draw_child(float pos_x, float pos_y);
	virtual void	mouse_button_callback(int window, int action, int mods);
	virtual void	cursor_position_callback(int status, double xpos, double ypos);
	virtual CAui	*why(float x, float y);
};

#endif