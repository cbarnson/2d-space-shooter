/**
 * @file Triangle.h
 * @brief definition of the Triangle class
 *
 * This class inherits the public members of the Drawable and Updateable interfaces
 *
 * @author Cody Barnson
 * @bug no known bugs
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector.h"
#include "Point.h"
#include "Drawable.h"
#include "Updateable.h"
#include <ctime>
#include <cstdlib>
#include <allegro5/allegro_primitives.h>

class Triangle : public Drawable, public Updateable {
  private:
   Point pt;
   int max_x, max_y, size;
   Vector crtSpeed;
      
  public:
  Triangle(int x, int y) : max_x(x), max_y(y), size(30), crtSpeed(0,100) {
      pt = Point(rand()% x, rand() % y);}      
   
   void draw() {
      if (pt.y > max_y) {
	 pt.y = -size;
	 pt.x = rand() % max_x;
      }	       
      al_draw_filled_triangle(pt.x, pt.y, pt.x+size, pt.y, pt.x+(size/2), pt.y+size,
		       al_map_rgb(0,0,255));
   }

   void update(double dt) {
      pt = pt + crtSpeed * dt; 
   }   
};

#endif
