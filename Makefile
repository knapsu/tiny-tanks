all:	obj	exe

dir:
	mkdir -p .objs-gcc

obj:	dir
	cd .objs-gcc && g++ -c ../*.cpp

exe:
	g++ `sdl-config --cflags` -o main .objs-gcc/*.o `sdl-config --cflags --libs` -lSDL_image -lSDL_mixer -lSDL_ttf

clean:
	rm -rf .objs-gcc main