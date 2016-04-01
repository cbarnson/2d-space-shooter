/**
 * @file Display.cc
 * @brief Implementation of Display class- launches display window
 *
 * @author
 * @bug
 */

#include "Display.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <iostream>

// constructor
Display::Display(int w, int h) {
   width = w;
   height = h;

   al_init();
	
   // if the display cannot be initialized, we should throw an
   // exception. We will deal with exceptons later in the course, so
   // for now, we simply exit
   if ((display = al_create_display(width, height)) == NULL) {
      std::cerr << "Cannot initialize the display\n";
      exit(1); // non-zero argument means "trouble"
   }

   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
}

// destructor
Display::~Display() {
   al_destroy_display(display);
}
