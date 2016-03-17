#ifndef ENEMY_H
#define ENEMY_H

#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <iostream>
#include <stdexcept>

using std::shared_ptr;
using std::make_shared;
using std::cout;

class Enemy : public Drawable, public Updateable {
  private:
   Point centre, end; 
   ALLEGRO_COLOR color;
   Vector speed;
	
   ALLEGRO_TIMER *fireDelay;
   shared_ptr<Sprite> death;
   //Sprite *death;

   Vector projSpeed;
   int size;
   int lives;
   int dAnim;
   
   bool dAnim_complete;
   bool dead;
   bool fire;
	
  public:
   // CONSTRUCTOR 1
  Enemy(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s)
   {
      if((fireDelay = al_create_timer(1.0 / 30)) == NULL)
	 throw std::runtime_error("cannot create fireDelay timer");
      al_start_timer(fireDelay);
      
      load_assets();
      
      projSpeed = speed * 1.5;
      
      lives = 1;
      size = 10;
      dAnim = 0;
      
      dAnim_complete = false;
      dead = false;
      fire = false;
      
   }
	
   ~Enemy();
   
   void setFire(bool f);
	
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed(); 
   Point getCentre();
   int getSize(); 
   
   bool getdAnim_complete(); 
   bool getDead(); 
   bool getFire(); 
   
   void update(double dt);
   void load_assets();
   void deathAnim();
   void hit();
   void draw();
};


#endif
