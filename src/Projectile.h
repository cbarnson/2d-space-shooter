/**
 * @file Projectile.h
 * @brief Declaration of Projectile interface
 *
 * @author
 * @bug
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <allegro5/allegro.h> // for color
#include <allegro5/allegro_primitives.h>

#include <iostream>

#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

class Projectile : public Drawable, public Updateable {
  public:
   Point centre;
   ALLEGRO_COLOR color;
   Vector speed;
   bool live;
   
   Projectile(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s)
   {
      live = true;
   }

   virtual ~Projectile() { }

   virtual void load_assets() = 0;
   
   void draw() { }
   void update(double dt) { }
   
};

#endif
