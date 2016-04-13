/**
 * @file Creep.h
 * @brief derived class of Enemy
 *
 * @author
 * @bug
 **/

#ifndef CREEP_H
#define CREEP_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <memory>
#include <ctime>
#include <cstdlib>

#include "Enemy.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include "Timer.h"

class Sprite;

extern const int CREEP_SIZE;

class Creep : public Enemy {
   
 public:
 Creep(Point p, ALLEGRO_COLOR c, Vector s) : Enemy(p, c, s),
    projSpeed(Vector(-400, 0)),
    fireSpeed(rand() % 50 + 30),
    lives(1), dAnim(0),
    dAnim_complete(false), fire(true) 
    {
      //load_assets();
      fireDelay = std::make_shared<Timer> (60);   
      fireDelay->create();
      fireDelay->startTimer();
    }

  ~Creep();
   
   void update(double dt);
   //void load_assets();
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
   
   // setters and getters
   void setFire(bool f);	
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed(); 
   int getSize();    
   Point getCentre();
   bool getDead(); 
   bool getFire();    
   bool getdAnim_complete();

  private:
   std::shared_ptr<Timer> fireDelay;   
   Vector projSpeed;
   int fireSpeed;
   int lives;
   int dAnim;   
   bool dAnim_complete;
   bool fire;
   
};
#endif
