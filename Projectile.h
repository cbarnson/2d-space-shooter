/**
 * @file Projectile.h
 * @brief
 *
 * @author
 * @bug
 */
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
   Point centre; // origin point
   ALLEGRO_COLOR color;
   Vector speed;   
   
   int size;
   bool live;
   
  public:
   
  Projectile(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s)
   {
      live = true;
      size = 5;
      centre = centre + speed * 0.1;
   }
   
   void setDead() { live = false; }
   
   Point getCentre() { return centre; }
   ALLEGRO_COLOR getColor() { return color; }
   Vector getSpeed() { return speed; }
   bool getLive() { return live; }
   
   void update(double dt) {
      centre = centre + speed * dt;
   }   
   void draw() {
      //al_draw_filled_rectangle(centre.x - size, centre.y - size,
      //			  centre.x + size, centre.y + size, color);
      Point tracer = centre + speed * (-0.1);
      al_draw_line(centre.x, centre.y, tracer.x, tracer.y, color, 3);
   }
   bool inBound() {
      if ((centre.x > 750) ||
	  (centre.x < 50) ||
	  (centre.y > 550) ||
	  (centre.y < 50)) {
	 return false; // out of bound
      }
      return true;
   }

};

#endif
