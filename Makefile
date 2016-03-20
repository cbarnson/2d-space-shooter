GPP = g++11
CFLAGS = -std=c++11 -Wall -I/home/lib2720/allegro/include
LIBDIR = /home/lib2720/allegro/lib
LNFLAGS = -lallegro -lallegro_primitives -lallegro_image -lallegro_font \
-lallegro_ttf
OBJECTS =  main.o Display.o Simulator.o engine.o Player.o Enemy.o Single.o \
Laser.o Missile.o

#Versus.o

#all : main

main : $(OBJECTS)
	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS)

%.o : %.cc
	$(GPP) -c $(CFLAGS) $^

#%.d: %.c
 #       @set -e; rm -f $@; \
  #       $(CC) -M $(CPPFLAGS) $< > $@.$$$$; \
   #      sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
#	rm -f $@.$$$$

main.o : Display.h Simulator.h engine.h

Display.o : Display.h
Simulator.o : Simulator.h
engine.o : engine.h Simulator.h Sprite.h Root.h
Player.o : Player.h
Enemy.o : Enemy.h
Laser.o : Laser.h
Missile.o : Missile.h
Single.o : Single.h Root.h
#Versus.o : Versus.h Root.h

clean :
	rm -f *.o *~ *% *# .#*

clean-all : clean
	rm -f *.gch main