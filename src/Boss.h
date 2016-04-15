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
//#include "Updateable.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

struct Point;
struct Vector;
class Timer;
class Sprite;

extern const int BOSS_HP;

class Boss : public Enemy {

  private:
   // timer
   std::shared_ptr<Timer> fireDelay;
   // general
   Vector projSpeed;
   int fireSpeed; 
   int lives;
   int dAnim;
   int hitbox;
   // flags
   bool dAnim_complete;
   bool fire;
   bool aliveBoss;
   bool targetable;
   // for animation
   int col, row, spriteSheetIndex;
   
  public:
   Boss (Point p, ALLEGRO_COLOR c, Vector s);
   ~Boss();


   // get methods
   ALLEGRO_COLOR getColor();
   Vector getProjSpeed();
   Point getCentre();
   int getSize();
   bool getdAnim_complete();
   bool getDead();
   bool getFire();
   bool getAlive();
   int getLives();

   // set methods
   void setFire(bool f);
   
   void update(double dt);
   void load_assets();
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void chooseFrame();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
};
#endif
