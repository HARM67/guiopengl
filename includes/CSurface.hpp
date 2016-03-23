#ifndef CSURFACE_HPP
# define CSURFACE_HPP
# include "CGraphic.hpp"

class	CSurface
{
	
	GLuint	vao;
	GLuint	vbo;
	GLuint	img;

	public:
		CSurface();
		~CSurface();

	void	Init();
	void	render();
};
#endif
