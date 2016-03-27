BIN = ogl
CC = g++
FLAG=-g
GLFW3_INCLUDES=-I LIB/glfw-3.1.2/include/
GLFW3_LIB=-L LIB/glfw-3.1.2/unix/src/
FREE_TYPE_LIB= -L ./LIB/freetype-2.4.0/objs/
INCLUDES=-I ./includes/  -I ./LIB/stb_image/ -I ./LIB/freetype-2.4.0/include/
#-I ./LIB/gl_util/
LIB= -lglfw3 -lfreetype
FRAMEWORK= -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
CSRCS = srcs/CApplication.cpp srcs/CGraphic.cpp srcs/CAui.cpp \
		srcs/CTexture.cpp srcs/CShader.cpp srcs/CAui_button.cpp srcs/CAui_cmd.cpp \
		srcs/CAui_window.cpp srcs/CAui_h_container.cpp  srcs/CAui_v_container.cpp \
		srcs/CImage.cpp srcs/CFont.cpp
SRC = srcs/main.cpp
L_SRCS=./LIB/stb_image/stb_image.c
#./LIB/gl_utils/gl_utils.cpp
#DEV_CMD = $(CSRCS:srcs/%cpp=-c \":vs ../includes/$$*hpp\" -c \":tabe ../srcs/$$*cpp\")
#DEV_CMD = $(CSRCS:srcs/%cpp=-c \":vs ../includes/%hpp  $(%)\")
DEV_CMD = `echo $(CSRCS) | sed 's/\(srcs\/\)\([a-zA-Z0-9_\.]*\).cpp/-c ":vs ..\/includes\/\2.hpp" -c ":tabe ..\/includes\/\2.cpp"/g'`


#DEV_CMD = $(CSRCS:%cpp=%hpp)

all:
		${CC} $(FLAG) -o ${BIN} ${SRC} $(CSRCS) $(L_SRCS) $(INCLUDES) $(FRAMEWORK) $(GLFW3_INCLUDES) $(GLFW3_LIB) $(LIB) $(FREE_TYPE_LIB)

dev:
	echo $(CSRCS) | sed 's/\(srcs\/\)\([a-zA-Z0-9_\.]*\).cpp/:tabe ..\/includes\/\2.hpp,:vs ..\/srcs\/\2.cpp,/g' | tr , "\n" > vim_config
	#echo ":vs CApplication.cpp\n" > vim_config
	vim -s vim_config srcs/main.cpp

