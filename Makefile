GPP = g++11
CFLAGS = -std=c++11 -Wall -I/home/lib2720/allegro/include
LIBDIR = /home/lib2720/allegro/lib
LNFLAGS = -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf
OBJECTS =  main.o Display.o Simulator.o Player.o Root.o

all : main

main : $(OBJECTS)
	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS)
%.o : %.cc
	$(GPP) -c $(CFLAGS) $^

main.o : Display.h Vector.h Point.h Drawable.h Updateable.h Controls.h engine.h Projectile.h Enemy.h Player.h Hotkeys.h

Display.o : Display.h

Simulator.o : Simulator.h Display.h Root.h

Player.o : Player.h Point.h Vector.h Updateable.h Drawable.h Controls.h Projectile.h Hotkeys.h Enemy.h

Root.o : Root.h Drawable.h Updateable.h Controls.h Projectile.h Enemy.h Player.h

clean :
	rm -f *.o *~ *% *# .#* *.gch

clean-all : clean
	rm -f main