/**
 * @file Laser.h
 * @brief derived class of Projectile
 *
 * @author
 * @bug
 */
#ifndef LASER_H
#define LASER_H

#include "Projectile.h"
#include "Point.h"
#include "Vector.h"
#include "Drawable.h"
#include "Updateable.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class Laser : public Projectile {
  public:
   Laser (Point p, ALLEGRO_COLOR c, Vector s)
      : Projectile(p, c, s)
   {
      
//load_assets();      
   }

   void load_assets();
   
   void draw();
   void update(double dt);
   
   bool in_bound();
   
};

#endif
