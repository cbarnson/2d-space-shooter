/**
 * @file Laser.cc
 * @brief Implementation of Laser class- draws, updates and destroys laser object
 *
 * @author
 */

#include "Laser.h"

void Laser::load_assets() {
   centre = centre + speed * 0.1; // so it doesn't hit its own projectile
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
   Point tracer = centre + speed * (-0.1);
   al_draw_line(centre.x, centre.y, tracer.x, tracer.y, color, 3);
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
