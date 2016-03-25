#ifndef CAUI_CMD_HPP
# define CAUI_CMD_HPP

# include "CGraphic.hpp"
# include "s_type.h"
# include "CAui.hpp"
# include <iostream>

class	CAui_cmd
{
private:
	CAui_cmd();
	~CAui_cmd(){};
	static CAui_cmd		m_instance;

public:
	CAui		*current;
	static CAui_cmd		*Instance()
	{
		return (&m_instance);
	};
	int		mouse_click();
};

#endif
