#ifndef ENEMY_H
#define ENEMY_H

#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include <iostream>//for testing, remove later
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
class Enemy : public Drawable, public Updateable {
  private:
   Point start, current, end;
   Vector speed;
   int size;
   
  public:
  Enemy(Point s, Point e, int spd, int size) : start(s.x, s.y), current(s.x, s.y),
      end(e.x, e.y), speed( (e.x-s.x)/spd, (e.y-s.y)/2) { }

   // draw image to display of enemy ship
   void draw() {
      std::cout<<"draw";
      al_draw_triangle(current.x, current.y,
			      current.x, current.y + size,
			      current.x - size*1.2, current.y + (size/2),
		       al_map_rgb(255,255,255), 1);
   }

   // update position of enemy ships
   void update(double dt) {
      //std::cout<<"updatehappened ";
      std::cout<<current.x<<", "<<current.y<<std::endl;
      current=current+speed*dt;
      if (current.x<=0)
      {
	 current.x=800;
      }
      

   }

};


#endif
