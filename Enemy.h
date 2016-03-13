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
   Point centre;
   ALLEGRO_COLOR color;
   Vector speed;
   
   int size;
   int lives;
   bool dead;
   
  public:
  Enemy(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s)
   {      
      lives = 1;
      dead = false;
      size = 20;
   }

   int getSize() { return size; }
   Point getCentre() { return centre; }
   
   void hit() {
      lives = lives - 1;
      if (lives < 1)
	 dead = true;
   }
   
   // draw image to display of enemy ship
   void draw() {
      al_draw_rectangle(centre.x - size, centre.y - size,
			centre.x + size, centre.y + size,
			color, 3);
   }

   // update position of enemy ships
   void update(double dt) {
      centre = centre + speed * dt;      
   }

};


#endif
