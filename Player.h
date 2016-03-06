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
#include "Hotkeys.h"
#include "Enemy.h"


class Player : public Controls, public Drawable, public Updateable {
  private:
   // list of all projectiles on screen
   std::list< std::shared_ptr<Projectile> > curProjectiles;
   // list of all enemies on screen
   std::list< std::shared_ptr<Enemy> > curEnemies;

   // player position (x,y)
   Point current;

   // size of player ship (in pixels), this variable gives us the freedom to modify the
   // player ship later
   int size;

   ALLEGRO_COLOR color;   
   std::shared_ptr<Hotkeys> config;   
   // player change in position
   Vector speed;
   int modifierSpeed;
   bool spawn = false;
   
  public:
  Player(Point p, int s, ALLEGRO_COLOR c, std::shared_ptr<Hotkeys> h) : current(p.x, p.y),
      size(s),
      color(c), config(h)
   {
      // sets initial speed to 0
      speed = Vector(0, 0);
      modifierSpeed = 100;
   }

   // called when ALLEGRO_EVENT_KEY_UP
   void set(int code) {
      for (int i = 0; i < 5; i++) {
	 if (code == config->control[i])
	    config->keys[i] = true;
      }
   }

   // called when ALLEGRO_EVENT_KEY_DOWN
   void reset(int code) {
      for (int i = 0; i < 5; i++) {
	 if (code == config->control[i])
	     config->keys[i] = false;
      }
   }   
   
   // draws a side-ways triangle (representing the player ship
   void draw() {
      al_draw_filled_triangle(current.x, current.y,
			      current.x, current.y + size,
			      current.x + size, current.y + (size/2),
			      color);
      if (!curEnemies.empty()) {
	 for (std::list< std::shared_ptr<Enemy> >::iterator it = curEnemies.begin();
	      it != curEnemies.end(); ++it) {
	    (*it)->draw();
	 }
      }
   }

   // function to interpret key pressed into a move command or shoot command
   // I decided to change the function to accept 2 parameters, to allow the movements to be
   // completely independent of eachother
   void updatePlayer() {
      // modifies the rate of change in position
      // up
      if (config->keys[0]) 
	 speed = Vector(speed.x, speed.y - modifierSpeed);
      // down
      if (config->keys[1]) 
	 speed = Vector(speed.x, speed.y + modifierSpeed); 
      
      // right
      if (config->keys[2]) 
	 speed = Vector(speed.x + modifierSpeed, speed.y);
      
      // left
      if (config->keys[3]) 
	 speed = Vector(speed.x - modifierSpeed, speed.y);
      
      // space - fire projectile
      if (config->keys[4]) {
	 std::shared_ptr<Projectile> new_proj =
	    std::make_shared<Projectile> (Point(current.x, current.y),
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
      if (!spawn) {
	 std::shared_ptr<Enemy> en = std::make_shared<Enemy> (Point(400, 300), Vector(-100,0));
	 curEnemies.push_back(en);
	 spawn = true;
      }

      if (!curEnemies.empty()) {
	 for (std::list< std::shared_ptr<Enemy> >::iterator it = curEnemies.begin();
	      it != curEnemies.end(); ++it) {
	    (*it)->update(dt);
	 }
      }
   }   
   
   
};

#endif
