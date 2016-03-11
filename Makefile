GPP = g++11
CFLAGS = -std=c++11 -Wall -I/home/lib2720/allegro/include
LIBDIR = /home/lib2720/allegro/lib
#LNFLAGS = -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf
LNFLAGS = -lallegro -lallegro_primitives
OBJECTS =  main.o Display.o Simulator.o

#OBJECTS = main.o

all : main

main : $(OBJECTS)
	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS)

%.o : %.cc
	$(GPP) -c $(CFLAGS) $^


main.o : Vector.h Point.h Drawable.h Updateable.h Controls.h gameSimulator.h Projectile.h Enemy.h Player.h Hotkeys.h

Display.o : Display.h

Simulator.o : Simulator.h

clean :
	rm -f *.o *~ *% *# .#*

clean-all : clean
	rm -f main