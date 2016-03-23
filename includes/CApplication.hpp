#ifndef CAPPLICATION_HPP
# define CAPPLICATION_HPP
# include <iostream>
# include "CGraphic.hpp"
# include "CAui.hpp"
# include "CSurface.hpp"
# include "CFile.hpp"
# include "CImage.hpp"

class	CApplication
{
	private:
	   CGraphic		*m_graphic;
	   CSurface		*m_surface;

	public:
		CApplication();
		~CApplication();
	
	void	init();
	void	render();
};
#endif
