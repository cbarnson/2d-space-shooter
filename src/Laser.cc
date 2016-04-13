/**
 * @file Laser.cc
 * @brief Implementation of Laser class- draws, updates and destroys laser object
 *
 * @author
 */
#include "Laser.h"

#include <allegro5/allegro_primitives.h>

void Laser::update(double dt) {
   _centre = _centre + _speed * dt;
   if (!in_bound())
     _dead = true;
}

void Laser::draw() {
   Point tracer = _centre + _speed * (-0.05);
   al_draw_line(_centre.x, _centre.y,
		tracer.x, tracer.y,
		_color, 3);		
}

bool Laser::in_bound() {
   if ((_centre.x > 800) ||
       (_centre.x < 0) ||
       (_centre.y > 600) ||
       (_centre.y < 0))
      return false;
   return true;
}
