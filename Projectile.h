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
   //double length; // represented by seconds traveling at param speed (which supplies direction)
   //bool live;
   //bool out;
   
  public:
   //bool out;
  Projectile(Point p, Vector s, ALLEGRO_COLOR c) : center(p), speed(s),
      color(c)
   {
      size = 5;
      //out = false;
      //live = true;
   }
   
   void draw() {
      //if (inBound()) {
	 al_draw_filled_rectangle(center.x - size, center.y - size,
				  center.x + size, center.y + size, color);
      
   }

   void update(double dt) {
      //if (inBound()) {
	 center = center + speed * dt;
	 //end = end + speed * dt;
	 //}
   }
   
   bool inBound() {
      if ((center.x > 750) ||
	  (center.x < 50) ||
	  (center.y > 550) ||
	  (center.y < 50)) {
	 return false; // out of bound
	 //out = true;
      }
      return true;
   }

};

#endif
