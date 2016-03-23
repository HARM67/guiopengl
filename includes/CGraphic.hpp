#ifndef CGRAPHIC_HPP
# define CGRAPHIC_HPP
//# include <GL/glew.h>
# include <stdio.h>
# include <iostream>
#define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

using namespace std;

class	CGraphic
{
	private:
		static CGraphic		m_instance;

		CGraphic();
		~CGraphic();


	public:
		GLFWwindow 			*m_window;
		static CGraphic		*Instance();
		//GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
};

#endif

