GPP = g++11
CFLAGS = -std=c++11 -Wall -I /home/lib2720/allegro/include/
LIBDIR = /home/lib2720/allegro/lib/
LNFLAGS = -lallegro -lallegro_primitives -lallegro_image
OBJECTS = Display.o main-square.o Simulator.o
OBJECT = Display.o mainrain.o Simulator.o
TREE = textinput.o

all: rain input
rain: $(OBJECT)
	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS)

input: $(TREE)
	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS)

%.o : %.cc
	$(GPP) $(CFLAGS) -c $^
mainrain.o: rainsimulator.h Triangle.h Drawable.h Updatable.h
#treebranch.o: rainsimulator.h Tree.h Drawable.h Updatable.h

clean:
	rm -f *.o *~ *% *# .#*
clean-all: clean
	rm -f mainrain treebranch
