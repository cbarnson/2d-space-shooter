
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
//#include "Sprite.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class Laser : public Projectile {
  private:
   bool in_bound();
   //int speedModifier;
   //shared_ptr<Sprite> laser;

  public:
   Laser (Point p, ALLEGRO_COLOR c, Vector s)
      : Projectile(p, c, s)
   { 
      load_assets();      
   }
   
   ~Laser();

   
   void load_assets();   
   void draw();
   void update(double dt);
   
   
};

#endif
