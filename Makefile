BIN = ogl
CC = g++
FLAG=-g
GLFW3_INCLUDES=-I LIB/glfw-3.1.2/include/
GLFW3_LIB=-L LIB/glfw-3.1.2/unix/src/
INCLUDES=-I ./includes/ -I ./lodepng/ -I ./LIB/stb_image/
LIB= -lglfw3
FRAMEWORK= -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
SRC = srcs/main.cpp lodepng/lodepng.cpp srcs/CApplication.cpp srcs/CGraphic.cpp srcs/CAui.cpp \
		srcs/CTexture.cpp \
		srcs/CSurface.cpp srcs/CFile.cpp srcs/CImage.cpp ./LIB/stb_image/stb_image.c 


all:
		${CC} $(FLAG) -o ${BIN} ${SRC} $(INCLUDES) $(FRAMEWORK) $(GLFW3_INCLUDES) $(GLFW3_LIB) $(LIB) 
