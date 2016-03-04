GPP = g++11
CFLAGS = -Wall -I/home/lib2720/allegro/include
LIBDIR = -L/home/lib2720/allegro/lib
LNFLAGS = -lallegro -lallegro_primitives -lallegro_dialog

OBJECTS =  main.o
#ALLEGRO_LIBRARIES := allegro-5 allegro_dialog-5
#ALLEGRO_FLAGS := $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES))

all : main

main : $(OBJECTS)
	$(GPP) $(CFLAGS) $(LIBDIR) $(LNFLAGS) -o $@

#main : $(OBJECTS)
#	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS)

#main : $(OBJECTS)
#	$(GPP) -L $(LIBDIR) -o $@ $^ $(ALLEGRO_FLAGS)
#rain : $(RAINOBJECTS)
#	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS) 

#tree : $(TREEOBJECTS)
#	$(GPP) -L $(LIBDIR) -o $@ $^ $(LNFLAGS) 

%.o : %.cc
	$(GPP) -c $(CFLAGS) $<


#%.o : %.cc
#	$(GPP) $(CFLAGS) -c $^

#main.o : Vector.h Point.h Drawable.h Updateable.h Triangle.h gameSimulator.h Message.h

#main-triangle.o : Vector.h Point.h Drawable.h Updateable.h Triangle.h mySimulator.h

#main-line.o : Vector.h Point.h Line.h Drawable.h Updateable.h Trunk.h mySimulator.h

clean :
	rm -f *.o *~ *% *# .#*

clean-all : clean
	rm -f main