#ifndef CGRAPHIC_HPP
# define CGRAPHIC_HPP
//# include <GL/glew.h>
# include <stdio.h>
# include <iostream>
# include <string>
# include <map>
# include "s_type.h"
# include "stb_image.h"
#define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

using namespace std;

class	CGraphic
{
	GLuint			m_vao;

	private:
	void	Init_surface();
		static CGraphic		m_instance;
		CGraphic();
		~CGraphic();

	public:
		GLuint	get_vao();
	float width;
	float height;
		GLFWwindow 			*m_window;
		static CGraphic		*Instance();
};

#endif

