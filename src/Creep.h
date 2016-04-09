/**
 * @file Creep.h
 * @brief derived class of Enemy
 *
 * @author
 * @bug
 **/

#ifndef CREEP_H
#define CREEP_H

#include "Enemy.h"
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

class Creep : public Enemy {
  private:
   Point centre, end; 
   ALLEGRO_COLOR color;
   Vector speed;
	
   ALLEGRO_TIMER *fireDelay;
   //shared_ptr<Sprite> death;
   //shared_ptr<Sprite> enemySprite;

   
   Vector projSpeed;
   int size;
   int lives;
   int dAnim;
   int fireSpeed;
   
   bool dAnim_complete;
   //bool dead;
   bool fire;
	
  public:
   // CONSTRUCTOR 1
  Creep(Point p, ALLEGRO_COLOR c, Vector s)
     : Enemy(p, c, s)
   {
      if((fireDelay = al_create_timer(1.0 / 30)) == NULL)
	 throw std::runtime_error("cannot create fireDelay timer");
      al_start_timer(fireDelay);
      
      load_assets();

      projSpeed = Vector(-500, 0);
      fireSpeed = (rand() % 20) + 80;  
      lives = 1;
      size = 20;
      
      dAnim = 0;      
      dAnim_complete = false;
      //dead = false;
      fire = true;
   }

   ~Creep();
   
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
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
};
#endif
