/**
 * @file Creep.h
 * @brief derived class of Enemy
 *
 * @author
 * @bug
 **/

#ifndef CREEPMIS_H
#define CREEPMIS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#include <memory>

#include "Enemy.h"
#include "Updateable.h"


struct Point;
struct Vector;
class Timer;
class Sprite;

//extern const int CREEP_SIZE;

class CreepMis : public Enemy {
   
  private:
   std::shared_ptr<Timer> fireDelay;   
   Vector projSpeed;
   int fireSpeed;
   int lives;
   int dAnim;   
   bool dAnim_complete;
   bool fire, at1, at2, at3, at4;
   Point stop1, stop2, stop3, stop4, next, focal;
   double angle;
  public:

   CreepMis(Point p, Point p2, Point p3, Point p4, Point p5, ALLEGRO_COLOR c, Vector s);
   ~CreepMis();
   
   void update(double dt);
   void load_assets();
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);   
   void setFire(bool f);
   void updateAngle();
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed(); 
   int getSize();    
   Point getCentre();
   bool getDead(); 
   bool getFire();    
   bool getdAnim_complete();

   
};
#endif
