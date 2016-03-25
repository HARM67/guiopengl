#ifndef CAPPLICATION_HPP
# define CAPPLICATION_HPP
# include <iostream>
# include "CGraphic.hpp"
# include "CAui.hpp"
# include "CAui_button.hpp"
//# include "CSurface.hpp"
//# include "CFile.hpp"
# include "CImage.hpp"
# include <stdlib.h>

class	CApplication
{
	t_position	pos;
	t_size	size;
private:
	   CGraphic		*m_graphic;

public:
		CApplication();
		~CApplication();
	
	void	init();
	void	render();
};
#endif
