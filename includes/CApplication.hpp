#ifndef CAPPLICATION_HPP
# define CAPPLICATION_HPP
# include <iostream>
# include "CGraphic.hpp"
# include "CAui.hpp"
# include "CAui_button.hpp"
# include "CAui_window.hpp"
# include "CAui_h_container.hpp"
# include "CAui_v_container.hpp"
# include "CFont.hpp"
# include "CAui_texte.hpp"
# include "CAui_loader.hpp"

# include "CImage.hpp"
# include <stdlib.h>

class	CApplication
{
	t_position	pos;
	t_size	size;
private:
	   CGraphic		*m_graphic;

public:
		CApplication(){};
		~CApplication(){};
	
	void	init();
	void	render();
};
#endif
