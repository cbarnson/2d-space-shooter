#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <allegro5/allegro.h> // for color
#include <allegro5/allegro_primitives.h>
#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

class Projectile : public Drawable, public Updateable {
  private:
   Point center; // origin point
   Vector speed;   
   ALLEGRO_COLOR color;
   int size;
   bool live;
   
  public:
   //Point center;
   //bool live;
   
  Projectile(Point p, Vector s, ALLEGRO_COLOR c) : center(p), speed(s),
      color(c)
   {
      live = true;
      size = 5;
   }

   
   
   void setLive(bool l) {
      live = l;
   }

   Point getCenter() {
      return center;
   }
   
   bool getLive() {
      return live;
   }
   
   void draw() {
	 al_draw_filled_rectangle(center.x - size, center.y - size,
				  center.x + size, center.y + size, color);
   }

   void update(double dt) {
	 center = center + speed * dt;
   }
   
   bool inBound() {
      if ((center.x > 750) ||
	  (center.x < 50) ||
	  (center.y > 550) ||
	  (center.y < 50)) {
	 return false; // out of bound
      }
      return true;
   }

};

#endif
