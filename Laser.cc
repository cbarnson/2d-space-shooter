/**
 * @file Laser.cc
 * @brief
 *
 * @author
 */

#include "Laser.h"

void Laser::load_assets() {
   centre = centre + speed * 0.1; // so it doesn't hit its own projectile

   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   laser = make_shared<Sprite> ("redLaserRay.png");
   al_destroy_path(path);
}

void Laser::update(double dt) {
   centre = centre + speed * dt;
   cout << "speed.x is " << speed.x << '\n';
   cout << "speed.y is " << speed.y << '\n';
   if (!in_bound())
      live = false;
   cout << "update in laser\n";
}

void Laser::draw() {
   //Point tracer = centre + speed * (-0.1);
   //al_draw_line(centre.x, centre.y, tracer.x, tracer.y, color, 3);
	laser->draw_tinted_scaled(centre, color, 0);
   cout << "draw in laser\n";
}

bool Laser::in_bound() {
   if ((centre.x > 800) ||
       (centre.x < 0) ||
       (centre.y > 600) ||
       (centre.y < 0))
      return false;
   return true;
}
