/**
 * @file Enemy.h
 * @brief Declaration of Enemy class
 *
 * @author
 * @bug

 Note: being changed to an interface
 */
#ifndef ENEMY_H
#define ENEMY_H

//#include "Drawable.h"
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

class Enemy : public Updateable {

   public:
   Point centre, end;
   ALLEGRO_COLOR color;
   Vector speed;
   ALLEGRO_TIMER *fireDelay;
   //im thinking they need
   bool dead;
   //bool dAnim_complete;
   
      
   Enemy (Point p, ALLEGRO_COLOR c, Vector s)
      : centre(p), color(c), speed(s)
   {
      //if((fireDelay = al_create_timer(1.0 / 30)) == NULL)
      // throw std::runtime_error("cannot create fireDelay timer");
      //al_start_timer(fireDelay);
      //projSpeed = Vector(-500, 0);
      //fireSpeed = (rand() % 20) + 80;  
      //lives = 1;
      //size = 20;
      dead = false;
      //bool dAnim_complete = false;
   }

   virtual ~Enemy() { }

   //void draw() { }
   //virtual void update(double dt) = 0;

   virtual void setFire(bool f) = 0;
   virtual ALLEGRO_COLOR getColor() = 0;
   virtual Vector getProjSpeed() = 0; 
   virtual Point getCentre() = 0;
   virtual int getSize() = 0;    
   virtual bool getdAnim_complete() = 0; 
   virtual bool getDead() = 0;
   virtual bool getFire() = 0;
   virtual void hit() = 0;
   virtual void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death) = 0;

   //virtual void setFire(bool f) { fire = f; }
   //virtual ALLEGRO_COLOR getColor() { return color; }
   //virtual Vector getProjSpeed() { return projSpeed; }
   //virtual int getSize() { return size; }
   //virtual Point getCentre() { return centre; }
   //virtual bool getDead() { return dead; }   
   //virtual bool getFire() { return fire; }
   //virtual bool getdAnim_complete() { return dAnim_complete; }

};

#endif
   
   /*private:
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

      projSpeed = Vector(-500, 0);
      fireSpeed = 20+ rand()%50;  
      lives = 1;
      size = 20;
      
      dAnim = 0;      
      dAnim_complete = false;
      dead = false;
      fire = true;
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
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
   */
//};

