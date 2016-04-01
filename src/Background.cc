/**
 * @file Background.cc
 * @brief Implementation of Background class- draws a moving background image
 *
 * @author
 * @bug
 */
#include "Background.h"

Background::Background(Vector bg_, Vector fg_) : bgSpeed(bg_), fgSpeed(fg_) {
   load_assets();
}

void Background::load_assets() {
   // represents the middle of the image width-wise, and top height-wise
   bgMid = Point(0, 0);
   fgMid = Point(0, 0);

   // get path to executable
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   
   // move to resources directory to access images
   al_change_directory(al_path_cstr(path, '/'));
   bg = std::make_shared<Sprite> ("BGstars.png");
   fg = std::make_shared<Sprite> ("FGstars.png");
   
   // delete the path
   al_destroy_path(path);       
}

// draw background and foreground images
void Background::draw() {
   bg->draw_parallax_background(bgMid.x, 0);
   fg->draw_parallax_background(fgMid.x, 0);
}

// update the position of the bitmap for which background and foreground will be drawn
void Background::update(double dt) {
   bgMid = bgMid + bgSpeed * dt;
   fgMid = fgMid + fgSpeed * dt;

   // background
   if (bgMid.x >= 800) {
      bgMid.x = 0;
   }
   
   // foreground
   if (fgMid.x >= 800) {
      fgMid.x = 0;
   }
}
