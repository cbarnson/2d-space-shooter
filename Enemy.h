#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

class Enemy : public Drawable, public Updateable {
  private:
   Point start, current;
   Vector speed;
   int size;
   
  public:
  Enemy(Point s, Vector spd) : start(s.x, s.y), speed(spd.x, spd.y)
   {
      current = Point(start.x, start.y);
      size = 50;
   }

   // draw image to display of enemy ship
   void draw() {
      al_draw_filled_triangle(current.x, current.y,
		       current.x, current.y + size,
		       current.x + size, current.y + (size/2),
		       al_map_rgb(204,204,0));
   }

   // update position of enemy ships
   void update(double dt) {
      current = current + speed * dt;      
   }

};


#endif
