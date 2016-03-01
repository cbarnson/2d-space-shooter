#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <cstdlib>

#include "Display.h"

Display::Display(int w, int h) {
	width = w;
	height = h;

	al_init();
	
	// if the display cannot be initialized, we should throw an
	// exception. We will deal with exceptons later in the course, so
	// for now, we simply exit
	if ((display = al_create_display(width, height)) == NULL) {
		std::cerr << "Cannot initialize the display" << std::endl;
		exit(1); // non-zero argument means "trouble"
	}

	al_init_primitives_addon();
}

Display::~Display() {
	al_destroy_display(display);
}
