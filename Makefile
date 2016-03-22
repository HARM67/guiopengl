BIN = ogl
CC = g++
FLAG=-g
GLFW3_INCLUDES=-I LIB/glfw-3.1.2/include/
GLFW3_LIB=-L LIB/glfw-3.1.2/unix/src/
INCLUDES=-I ./includes/
LIB= -lglfw3
FRAMEWORK= -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
SRC = srcs/main.cpp 
#srcs/OglInit.cpp

all:
		${CC} $(FLAG) -o ${BIN} ${SRC} $(INCLUDES) $(FRAMEWORK) $(GLFW3_INCLUDES) $(GLFW3_LIB) $(LIB) 
