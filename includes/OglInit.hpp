#ifndef OGLINIT_HPP
# define OGLINIT_HPP
//# include <GL/glew.h>
# include <stdio.h>
# include <iostream>
#define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>

using namespace std;

class	OglInit
{
	public:
		OglInit();
		~OglInit();

	GLFWwindow *window;
	void	close();
	static void	mouse(GLFWwindow *window, double x, double y)
	{
		cout << x << " " << y << endl;
	}

	void	render();
};

#endif

