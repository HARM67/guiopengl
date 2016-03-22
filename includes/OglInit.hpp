#ifndef OGLINIT_HPP
# define OGLINIT_HPP
//# include <GL/glew.h>
# include <stdio.h>
# include <iostream>
# include <GL/glew.h>
# include <GLFW/glfw3.h>

using namespace std;

class	OglInit
{
	public:
		OglInit();
		~OglInit();

	GLFWwindow *window;
	GLFWwindowclosefun		close();
	static void	mouse(GLFWwindow *window, double x, double y)
	{
		cout << x << " " << y << endl;
	}

	void	render();
};

#endif

