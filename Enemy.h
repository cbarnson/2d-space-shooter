#ifndef ENEMY_H
#define ENEMY_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include <iostream>//for testing, remove later
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
class Enemy : public Drawable, public Updateable {
  private:
   Point start, current;
   Vector speed;
   int size;
   
  public:
<<<<<<< HEAD
  Enemy(Point s, Vector spd) : start(s.x, s.y), speed(spd.x, spd.y)
   {
      current = Point(start.x, start.y);
      size = 50;
=======
  Enemy(Point s, Point e) : start(s.x, s.y), end(e.x, e.y){
      current=Point(start.x, start.y);
      speed.x=(end.x-start.x)/5.0;
      speed.y=(end.y-start.y)/5.0;
      size=20;

>>>>>>> a800d4ddb56872166ca8bb047b962c4930685cce
   }

   // draw image to display of enemy ship
   void draw() {
<<<<<<< HEAD
      al_draw_filled_triangle(current.x, current.y,
		       current.x, current.y + size,
		       current.x + size, current.y + (size/2),
		       al_map_rgb(204,204,0));
=======
      // std::cout<<"draw";
      al_draw_filled_triangle(current.x, current.y,
			      current.x, current.y + size,
			      current.x - size, current.y + (size/2),
			      al_map_rgb(255,255,255));
>>>>>>> a800d4ddb56872166ca8bb047b962c4930685cce
   }

   // update position of enemy ships
   void update(double dt) {
<<<<<<< HEAD
      current = current + speed * dt;      
=======
      //std::cout<<"updatehappened ";
      //std::cout<<current.x<<", "<<current.y<<std::endl;
      Point newCurrent=current;
      newCurrent=current+speed*dt;
      if (newCurrent.x<=0)
      {
	 newCurrent.x=800;
      }
      if(newCurrent.y<=0)
      {
	 this->speed.y=speed.y*-1.0;
      }
      if(newCurrent.y>=600-size)
      {
	 this->speed.y=speed.y*-1.0;
      }
     
      current=newCurrent;
>>>>>>> a800d4ddb56872166ca8bb047b962c4930685cce
   }

};


#endif
