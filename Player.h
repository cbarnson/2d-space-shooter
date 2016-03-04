#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <memory>
#include "Point.h"
#include "Vector.h"
#include "Drawable.h"
#include "Controls.h"
#include "Projectiles.h"
#include "Enemy.h"

class Player : public Controls, public Drawable {
  private:
   // list of all projectiles on screen
   std::list< std::shared_ptr<Projectile> > curProjectiles;
   // list of all enemies on screen
   std::list< std::shared_ptr<Enemy> > curEnemies;

   // player position
   Point current;
   // player change in position
   Vector speed;
   // size of player ship
   int size;
   
  public:
   Player();
   
   


   
};

#endif
