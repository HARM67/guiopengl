#include "CSurface.hpp"

CSurface::CSurface()
{

}

CSurface::~CSurface()
{

}
GLuint loadBMP_custom(const char * imagepath)
{
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	unsigned char * data;
	
	FILE * file = fopen(imagepath,"rb");
	if (!file){printf("Image could not be opened\n"); return 0;}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
		    printf("Not a correct BMP file\n");
			    return false;
	}
	if ( header[0]!='B' || header[1]!='M' ){
		    printf("Not a correct BMP file\n");
			    return 0;
	}
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54;
	data = new unsigned char [imageSize];

	fread(data,1,imageSize,file);
	fclose(file);
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	return (textureID);
}

void	CSurface::Init()
{
	CGraphic	*graphic = CGraphic::Instance();


	GLuint vs, fs;
	GLuint shader_programme;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	static const GLfloat g_uv_buffer_data[] = {
		-1.0f, 1.0f,
		1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, 1.0f,
		1.0f, -1.0f,
		-1.0f, -1.0f,
	};

	GLfloat	points[] = {
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
	};
	
	/*
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	*/char* vertex_shader =
	"#versio n 330 core"
		"layout(location = 0) in vec3 vertexPosition_modelspace;"
		"layout(location = 1) in vec2 vertexUV;"
		"out vec2 UV;"
		"uniform mat4 MVP;"
		"void main(){"
		"	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);"
		"	UV = vertexUV;"
		"}";
/*
	"#version 410\n"
	"in vec3 vp;"
	"void main() {"
	"	gl_Position = vec4 (vp, 1.0);"
	"}";
*/
	char *fragment_shader =
	"#version 330 core"
	"in vec2 UV;"
	"out vec3 color;"
	"uniform sampler2D myTextureSampler;"
	"void main(){"
	"        color = texture( myTextureSampler, UV ).rgb;"
	"}";
/*
		"#version 410\n"
		"out vec4 frag_colour;"
		"void main () {"
		"	frag_colour = vec4 (1.0, 1.0, 1.0, 0.5);"
		"}";
*/

	glGenBuffers (1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), points,
			GL_STATIC_DRAW);

	glGenVertexArrays (1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	img= loadBMP_custom("lena.bmp");
	printf("%u", img);

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
	while( glfwGetKey(graphic->m_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
			glfwWindowShouldClose(graphic->m_window) == 0)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram (shader_programme);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glfwPollEvents();
		glfwSwapBuffers(graphic->m_window);
	}
}

void	CSurface::render()
{

}
