GPP = g++11
CFLAGS = -std=c++11 -Wall -I /home/lib2720/allegro/include/
LIBDIR = /home/lib2720/allegro/lib/
LNFLAGS = -lallegro -lallegro_primitives -lallegro_image
RAINOBJECTS = Display.o main-triangle.o Simulator.o
TREEOBJECTS = Display.o main-line.o Simulator.o

all : rain tree

rain : $(RAINOBJECTS)
	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS) 

tree : $(TREEOBJECTS)
	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS) 

%.o : %.cc
	$(GPP) $(CFLAGS) -c $^

main-triangle.o : Vector.h Point.h Drawable.h Updateable.h Triangle.h mySimulator.h

main-line.o : Vector.h Point.h Line.h Drawable.h Updateable.h Trunk.h mySimulator.h

clean :
	rm -f *.o *~ *% *# .#*

clean-all : clean
	rm -f rain tree