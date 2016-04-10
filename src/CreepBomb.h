/**
 * @file Creep.h
 * @brief derived class of Enemy
 *
 * @author
 * @bug
 **/

#ifndef CREEPBOMB_H
#define CREEPBOMB_H

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
#include "Timer.h"
#include "Root.h"

using std::shared_ptr;
using std::make_shared;

class CreepBomb : public Enemy {
  private:
   Point centre, end; 
   ALLEGRO_COLOR color;
   Vector speed;
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
   std::shared_ptr<Timer> fireDelay;
	
  public:
   // CONSTRUCTOR 1
  CreepBomb(Point p, ALLEGRO_COLOR c, Vector s)
     : Enemy(p, c, s), centre(p), color(c), speed(s)
   {
      // speed.x=-50; speed.y=0;y
      projSpeed= Vector(-500, 0);//not used
      fireDelay=std::make_shared<Timer> (60);
      fireDelay->startTimer();

      lives = 3;
      size = 20;
      
      dAnim = 0;      
      dAnim_complete = false;
      // dead = false;
      fire = false;
      //std::cout<<
   }

   ~CreepBomb();
   
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
