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

#include "Enemy.h"
#include "Updateable.h"

struct Point;
struct Vector;
class Timer;
class Sprite;

extern const int CREEP_SIZE;

class Creep : public Enemy {
   
  private:
   std::shared_ptr<Timer> fireDelay;   
   Vector projSpeed;
   int fireSpeed;
   int lives;
   int dAnim;   
   bool dAnim_complete;
   bool fire;
	
  public:
   Creep(Point p, ALLEGRO_COLOR c, Vector s);
   ~Creep();
   
   void update(double dt);
   void load_assets();
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
   
   void setFire(bool f);	
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed(); 
   int getSize();    
   Point getCentre();
   bool getDead(); 
   bool getFire();    
   bool getdAnim_complete();
   
   
};
#endif
