/**
 * @file Player.h
 * @brief class definition of the Player class
 *
 * This class inherits public members of Controls and Drawable
 *
 * @author
 * @bug
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <list>
#include <memory>
#include "Point.h"
#include "Vector.h"
#include "Drawable.h"
#include "Controls.h"
#include "Projectile.h"
#include "Enemy.h"


class Player : public Controls, public Drawable, public Updateable {
  private:
   // list of all projectiles on screen
   std::list< std::shared_ptr<Projectile> > curProjectiles;
   // list of all enemies on screen
   std::list< std::shared_ptr<Enemy> > curEnemies;

   // player position (x,y)
   Point current;
   // player change in position
   Vector speed;
   // size of player ship (in pixels), this variable gives us the freedom to modify the
   // player ship later
   int size;
   int modifierSpeed;
   
  public:
  Player(Point p, int s) : current(p.x, p.y), size(s)
   {
      // sets initial speed to 0
      speed = Vector(0, 0);
      modifierSpeed = 100;
   }

   // draws a side-ways triangle (representing the player ship
   void draw() {
      al_draw_filled_triangle(current.x, current.y,
			      current.x, current.y + size,
			      current.x + size, current.y + (size/2),
			      al_map_rgb(0,204,0));      
   }

   // function to interpret key pressed into a move command or shoot command
   // I decided to change the function to accept 2 parameters, to allow the movements to be
   // completely independent of eachother
   void updatePlayer(std::vector<bool>& v) {
      // up
      if (v[0]) {
	 speed = Vector(speed.x, speed.y - modifierSpeed); // modifies the rate of change in position
	 //current = current + speed * dt;	 // updates the position
      }
      //else speed = Vector(0, 0); // we need to reset the speed after the pos has been updated
      
      // down
      if (v[1]) {
	 speed = Vector(speed.x, speed.y + modifierSpeed); 
	 //current = current + speed * dt;
      }
      //else speed = Vector(0, 0);
      
      // right
      if (v[2]) {
	 speed = Vector(speed.x + modifierSpeed, speed.y);
	 //current = current + speed * dt;
      }
      //else speed = Vector(0, 0);
      
      // left
      if (v[3]) {
	 speed = Vector(speed.x - modifierSpeed, speed.y);
	 //current = current + speed * dt;
      }
      //else speed = Vector(0, 0);
      
      // space - fire projectile
      if (v[4]) {
	 std::shared_ptr<Projectile> new_proj = std::make_shared<Projectile> (Point(current.x, current.y),
									      Vector(modifierSpeed * 2, 0));
	 curProjectiles.push_back(new_proj);
      }

      
   }
   
   // update handles all the position changes for all objects that are NOT the player   
   void update(double dt) {
      // ...
      // code for updating all the Enemy objects and Projectile objects goes here
      // members curProjectiles and curEnemies should be updated iteratively
      // ...
      // collision detection may also end up going here
      current = current + speed * dt;
      speed = Vector(0, 0);
      
      
   }   
   
   
};

#endif
