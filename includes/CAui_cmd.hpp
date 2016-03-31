#ifndef CAUI_CMD_HPP
# define CAUI_CMD_HPP

# include "CGraphic.hpp"
# include "s_type.h"
# include "CAui.hpp"
# include <iostream>

# define TIME_NEXT_KEY 0.2f
# define TIME_MOVE_KEY 0.1f

class	CAui_cmd
{
private:
	CAui_cmd();
	~CAui_cmd(){};
	static CAui_cmd		m_instance;

public:
	static double 			command[512];
	static unsigned char	b_key[512];
	CAui		*current;
	CAui		*focus;
	static CAui_cmd		*Instance()
	{
		return (&m_instance);
	};
	int		mouse_click();
};

#endif
