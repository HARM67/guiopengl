#include "OglInit.hpp"

OglInit::OglInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

/*
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
*/
	window = glfwCreateWindow(1024, 768, "Salut", NULL, NULL);
	glfwMakeContextCurrent(window);
//	glfwSetWindowPos(window, 100, 100);
//	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
}

OglInit::~OglInit()
{
	close();
}

void	OglInit::render()
{
	const GLubyte *renderer;
	const GLubyte *version;
	GLuint	vao;
	GLuint vbo;

	GLfloat points[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-1.5f, -0.5f, 0.0f
	};

	const	char* vertex_shader =
	"#version 410\n"
	"in vec3 vp;"
	"void main() {"
	"	gl_Position = vec4 (vp, 1.0);"
	"}";

	const char *fragment_shader =
		"#version 410\n"
		"out vec4 frag_colour;"
		"void main () {"
		"	frag_colour = vec4 (0.5, 0.0, 0.5, 1.0);"
		"}";
	GLuint vs, fs;
	GLuint shader_programme;

	renderer = glGetString (GL_RENDERER);
	version = glGetString (GL_VERSION);
	printf("%s\n", renderer);
	printf("%s\n", version);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glGenBuffers (1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), points,
			GL_STATIC_DRAW);

	glGenVertexArrays (1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	vs = glCreateShader (GL_VERTEX_SHADER);
	glShaderSource (vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	shader_programme = glCreateProgram ();
	glAttachShader(shader_programme, fs);
	glAttachShader(shader_programme, vs);
	glLinkProgram (shader_programme);

	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram (shader_programme);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}

void	OglInit::close()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

