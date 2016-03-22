/**
 * @file Laser.cc
 * @brief Implementation of Laser class- draws, updates and destroys laser object
 *
 * @author
 */

#include "Laser.h"

Laser::~Laser() {
   
}

void Laser::load_assets() {
   centre = centre + speed * 0.1; // so it doesn't hit its own projectile
   
   //ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   //al_append_path_component(path, "resources");
   //al_change_directory(al_path_cstr(path, '/'));
   
   //laser = make_shared<Sprite> ("Laser2.png");
   
   //al_destroy_path(path);
}

void Laser::update(double dt) {
   centre = centre + speed * dt;
   if (!in_bound())
      live = false;
}

void Laser::draw() {
   //laser->draw_tinted(centre, color, 0);
   al_draw_line(centre.x, centre.y,
		centre.x + speed.x * (-0.1),
		centre.y + speed.y * (-0.1),
		color, 3);		
}

bool Laser::in_bound() {
   if ((centre.x > 800) ||
       (centre.x < 0) ||
       (centre.y > 600) ||
       (centre.y < 0))
      return false;
   return true;
}
