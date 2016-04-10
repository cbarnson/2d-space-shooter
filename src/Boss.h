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
#include "Drawable.h"
#include "Updateable.h"
#include "Point.h"
#include "Vector.h"
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <memory>

using std::shared_ptr;
using std::make_shared;

class Boss : public Enemy {
  private:
   ALLEGRO_TIMER *fireDelay;
   shared_ptr<Sprite> bShip;
   
   Vector projSpeed;
   int size; //after it works in this state, check to see if I can move size and lives
   int lives;//to the Enemy.h i feel like some others can go tooo....
   int dAnim;
   int fireSpeed;

   bool dAnim_complete;
   bool fire;
   
  public:
   Boss (point p, ALLEGRO_COLOR c, Vector s)
      : Enemy(p, c, s)
   {
      if((fireDelay = al_create_timer(1.0 / 30)) == NULL)
	 throw std::runtime_error("cannot create fireDelay timer");
      al_start_timer(fireDelay);

      load_assets();

      projSpeed = Vector(-500, 0);
      fireSpeed = (rand() %20) + 10;

      lives = 20;
      size = 150;

      dAnim = 0;
      dAnim_complete = false;
      fire = true;
   }
   
   ~Boss();
   
   ALLEGRO_COLOR getcolor();
   Vector getProjSpeed();
   Point getCentre();
   int getSize();
   
   bool getAnim_complete();
   bool getDead();
   bool getFire();

   void setFire(bool f);
   void update(double dt);
   void load_assets();
   void deathAnim(std::shared_ptr<Sprite>);
   void hit();
   void draw(std::shared_ptr<Sprite> ship, std::shared_ptr<Sprite> death);
};
#endif
