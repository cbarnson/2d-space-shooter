#ifndef ENEMY_H
#define ENEMY_H

#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>

class Enemy : public Drawable, public Updateable {
  private:
   Point centre;
   ALLEGRO_COLOR color;
   Vector speed;
   
   ALLEGRO_TIMER *fireDelay = NULL;

   Vector projSpeed;
   int size;
   int lives;
   bool dead;
   bool fire;
	
  public:
   // CONSTRUCTOR 1
  Enemy(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s)
   {
      if((fireDelay = al_create_timer(1.0 / 30)) == NULL)
	 throw std::runtime_error("cannot create fireDelay timer");
      al_start_timer(fireDelay);
      
      lives = 1;
      size = 10;
      dead = false;
      fire = false;
      projSpeed = speed * 1.5;
   }
   
   // CONSTRUCTOR 2
   /*
  Enemy(Point s, Point e, ALLEGRO_COLOR c) : centre(s), end(e), color(c)
   {
      lives=1;
      dead=false;
      size=20;
      speed.x=(end.x/centre.x)/intspeed;
      speed.y=(end.y/centre.y)/intspeed;
   }
   */
   ~Enemy() {
      if(fireDelay != NULL)
	 al_destroy_timer(fireDelay);
   }


   
   void setFire(bool f) { fire = f; }
   
   ALLEGRO_COLOR getColor() { return color; }
   Vector getProjSpeed() { return projSpeed; }
   int getSize() { return size; }
   Point getCentre() { return centre; }
   bool getDead() { return dead; }
   bool getFire() { return fire; }

   
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
      
      // check x bound and adjust if out
      if (centre.x < 0)
	 dead = true;      
      // check y bound and adjust if out
      if (centre.y > 600 - size)
	 speed.y = -speed.y;
      else if (centre.y < size)
	 speed.x = -speed.x;

      
      if(al_get_timer_count(fireDelay) > 80){
	 fire = true;
	 al_stop_timer(fireDelay);
	 al_set_timer_count(fireDelay, 0);
	 al_start_timer(fireDelay);
      }    
   }
   

   
   /*
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
   bool getDead() { return dead; }
   
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
   */
};


#endif
