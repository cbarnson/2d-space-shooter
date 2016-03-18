GPP = g++11
CFLAGS = -std=c++11 -Wall -I/home/lib2720/allegro/include
LIBDIR = /home/lib2720/allegro/lib
LNFLAGS = -lallegro -lallegro_primitives -lallegro_image -lallegro_font \
-lallegro_ttf
OBJECTS =  main.o Display.o Simulator.o engine.o Player.o Enemy.o Single.o \
Versus.o Laser.o

#all : main

main : $(OBJECTS)
	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS)
%.o : %.cc
	$(GPP) -c $(CFLAGS) $^

main.o : Display.h Simulator.h engine.h

Display.o : Display.h
Simulator.o : Simulator.h Display.h
engine.o : engine.h Simulator.h Sprite.h Root.h
Player.o : Player.h Point.h Vector.h Projectile.h Hotkeys.h Enemy.h Sprite.h 
Enemy.o : Enemy.h Vector.h Sprite.h
Laser.o : Laser.h Projectile.h Point.h Vector.h Sprite.h
Single.o : Single.h Root.h
Versus.o : Versus.h Root.h

clean :
	rm -f *.o *~ *% *# .#*

clean-all : clean
	rm -f *.gch main