/**
 * @file Background.cc
 * @brief Implementation of Background class- draws a moving background image
 *
 * @author
 * @bug
 */
#include "Background.h"

void Background::load_assets() {
   origin = Point(800, 300);
   bgCentre = origin;
   fgCentre = origin;
   
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   bg = make_shared<Sprite> ("BGstars.png");
   fg = make_shared<Sprite> ("FGstars.png");
   
   al_destroy_path(path);       
}

void Background::draw() {
   bg->draw(bgCentre, 0);
   fg->draw(fgCentre, 0);
}

void Background::update(double dt) {
   bgCentre = bgCentre + bgSpeed * dt;
   fgCentre = fgCentre + fgSpeed * dt;      
   
   if (bgCentre.x <= 0) {
      bgCentre = origin;
   }
   if (fgCentre.x <= 0) {
      fgCentre = origin;
   }
}
