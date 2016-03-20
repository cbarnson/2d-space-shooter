/**
 * @file Projectile.h
 * @brief Declaration of Projectile interface
 *
 * @author
 * @bug
 */
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

#include <allegro5/allegro.h> // for color
#include <allegro5/allegro_primitives.h>
#include <iostream>

using std::cout;

class Projectile : public Drawable, public Updateable {
  public:
   Point centre;
   ALLEGRO_COLOR color;
   Vector speed;
   bool live;
   
   Projectile (Point p, ALLEGRO_COLOR c, Vector s)
      : centre(p), color(c), speed(s)
   {
      live = true;
      //centre = centre + speed * 0.1;
   }

   virtual ~Projectile() { }
   
   void draw() { };
   void update(double dt) { };
   
};

#endif

   /*
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
      if ((centre.x > 800) ||
	  (centre.x < 0) ||
	  (centre.y > 600) ||
	  (centre.y < 0)) {
	 return false; // out of bound
      }
      return true;
      }
   */

