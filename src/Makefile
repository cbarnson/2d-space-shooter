
# Cody Barnson
# Thur Mar 31, 2016
# Makefile for allegro game project

# declaration of variables
CC = g++
#CCFLAGS = -Wall -g -std=c++11 -I/home/lib2720/allegro/include
CCFLAGS = -Wall -g -std=c++11 `pkg-config --cflags allegro-5.0`

# file names
SOURCES = $(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
#LIBDIR = -L/home/lib2720/allegro/lib
#LNFLAGS = -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf
LNFLAGS = `pkg-config --libs allegro-5.0` -lallegro_primitives \
-lallegro_font -lallegro_ttf -lallegro_image


# main target
all: main


main: $(OBJECTS)
	$(CC) -o $@ $^ $(LNFLAGS)
#	$(CC) $(OBJECTS) -o main

# pull in dependency info for existing .o files
-include $(OBJECTS:.o=.d)

# compile and generate dependency info
%.o: %.cc
	$(CC) -c $(CCFLAGS) $< -o $@
	$(CC) -M $(CCFLAGS) $*.cc > $*.d



# automatic variables
# $< contains the first dependency file name
# $@ contains the target file name

# phony targets --> avoid conflict with file of the same name, and
#                   improve performance
.PHONY: clean

# clean out the directory but keep executables with command "clean"
clean : 
	rm -f *~ *.o *.d *.gch main




