/**
 * @file Boss.h
 * @brief derived class of Enemy
 *
 * @author
 * @bugs lots
 *
 **/

#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"
//#include "Drawable.h"
#include "Updateable.h"
//#include "Point.h"
//#include "Vector.h"
//#include "Sprite.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

//using std::shared_ptr;
//using std::make_shared;

struct Point;
struct Vector;
class Timer;
class Sprite;

extern const int BOSS_SIZE;

class Boss : public Enemy {

  private:
   std::shared_ptr<Timer> fireDelay;
   Vector projSpeed;
   //Point centre;
   //ALLEGRO_COLOR color;
   //Vector speed;
   //ALLEGRO_TIMER *fireDelay;
   //shared_ptr<Sprite> bShip;
   //int size; 
   int fireSpeed;
   int lives;
   int dAnim;
   bool dAnim_complete;
   bool fire;
   bool aliveBoss;
   
  public:
   Boss (Point p, ALLEGRO_COLOR c, Vector s);
   /*: Enemy(p, c, s), centre(p), color(c), speed(s)
   {
      if((fireDelay = al_create_timer(1.0 / 30)) == NULL)
	 throw std::runtime_error("cannot create fireDelay timer");
      al_start_timer(fireDelay);
      load_assets();

      projSpeed = Vector(-300, 0);
      fireSpeed = (rand() %10) + 10;

      lives = 50;
      size = 70;

      dAnim = 0;
      dAnim_complete = false;
      fire = true;
      aliveBoss = true;
      }*/
   
   ~Boss();
   
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed();
   Point getCentre();
   int getSize();

   bool getdAnim_complete();
   bool getDead();
   bool getFire();
   bool getAlive();

   void setFire(bool f);
   void update(double dt);
   void load_assets();
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
};
#endif
