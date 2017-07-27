#
CPP=g++
CCOPTS=-g -Wno-deprecated -Wall
SDL_CONFIG=sdl-config

####################################################################
CPPFLAGS=`$(SDL_CONFIG) --cflags` $(CCOPTS)
LINKFLAGS=`$(SDL_CONFIG) --libs`
LINKLIBS=\
		-lSDL_ttf\
		-lGL
LINKPATHS=

########################  Objects to build #######################
OBJECTS=\
	AppContext.o\
	EventHandler.o\
	MainWindow.o\
	Renderer.o\
	RendererOpenGL.o\
	TiledFont.o\
	main.o

glclock:	$(OBJECTS) LiberationMono-Bold.ttf
	$(CPP) $(CPPFLAGS) $(OBJECTS) $(LINKFLAGS) $(LINKPATHS) $(LINKLIBS) -o $@

LiberationMono-Bold.ttf: /usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf
	ln -s /usr/share/fonts/truetype/liberation/LiberationMono-Bold.ttf

clean:
	rm -f *.o *.gch *.ttf glclock

###########################  Conversions   ########################

.SUFFIXES: .cpp .o

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $<

