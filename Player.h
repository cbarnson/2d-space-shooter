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
#include <iostream>
#include "Point.h"
#include "Vector.h"
#include "Drawable.h"
#include "Controls.h"
#include "Projectile.h"
#include "Hotkeys.h"
#include "Enemy.h"

using std::list;
using std::shared_ptr;
using std::make_shared;
using std::vector;

class Player : public Controls, public Drawable, public Updateable {
  private:
   list< shared_ptr<Projectile> > curProjectiles;
   list< shared_ptr<Enemy> > curEnemies;

   Point current;       // ship position
   ALLEGRO_COLOR color; // ship color
   Hotkeys config;      // key mapping profile
   bool flipped;
   Vector speed;        // movement speed in any direction
   Vector projSpeed;    // speed of projectiles
   int xModifier;       // x movement speed
   int yModifier;       // y movement speed
   int size;            // ship size in pixels
   
  public:
  Player(Point p, ALLEGRO_COLOR c, vector<int> h, bool f) : current(p),
      color(c), config(h), flipped(f)
   {
      speed = Vector(0, 0);      
      xModifier = 150;
      yModifier = 150;
      
      if (flipped) {
	 size = 50;
	 projSpeed = Vector(200, 0);
      }
      else {
	 size = -50;
	 projSpeed = Vector(-200, 0);
      }
   }

   // called when ALLEGRO_EVENT_KEY_UP
   void set(int code) {
      for (int i = 0; i < 5; i++) {
	 if (code == config.control[i])
	    config.keys[i] = true;
      }
   }

   // called when ALLEGRO_EVENT_KEY_DOWN
   void reset(int code) {
      for (int i = 0; i < 5; i++) {
	 if (code == config.control[i])
	     config.keys[i] = false;
      }
   }   
   
   // draws a side-ways triangle (representing the player ship
   // note: the first coordinate is the tip of the ship
   void draw() {
      al_draw_filled_triangle(current.x, current.y,
			      current.x - size, current.y + 0.5 * size,
			      current.x - size, current.y - 0.5 * size,
			      color);

      // ENEMIES
      if (!curEnemies.empty()) {
	 for (list< shared_ptr<Enemy> >::iterator it = curEnemies.begin();
	      it != curEnemies.end(); ++it) {
	    (*it)->draw();
	 }
      }

      // PROJECTILES
      if (!curProjectiles.empty()) {
	 for (list< shared_ptr<Projectile> >::iterator it = curProjectiles.begin();
	      it != curProjectiles.end(); ++it) {
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
      if (config.keys[0]) 
	 speed.yMod(-yModifier);
      // down
      if (config.keys[1])
	 speed.yMod(yModifier);
      // right
      if (config.keys[2]) 
	 speed.xMod(xModifier);      
      // left
      if (config.keys[3]) 
	 speed.xMod(-xModifier);
      // space - fire projectile
      if (config.keys[4]) {
	 shared_ptr<Projectile> new_proj = make_shared<Projectile> (current, projSpeed,
								    color);
	 curProjectiles.push_back(new_proj);
      }
   }
   
   // update handles all the position changes for all objects that are NOT the player   
   void update(double dt) {
      // check boundary

      current = current + speed * dt;
      speed = Vector(0, 0);
      
      // ENEMIES
      if (!curEnemies.empty()) {
	 for (list< shared_ptr<Enemy> >::iterator it = curEnemies.begin();
	      it != curEnemies.end(); ++it) {
	    (*it)->update(dt);
	 }
      }


      // PROJECTILES
      if (!curProjectiles.empty()) {	 
	 list< shared_ptr<Projectile> > newList;	 
	 for (list< shared_ptr<Projectile> >::iterator it = curProjectiles.begin();
	      it != curProjectiles.end(); ++it) {	    
	    (*it)->update(dt);
	    if ((*it)->inBound()) 
	       newList.push_back(*it); // build the new list	    	    
	 }
	 
	 curProjectiles.clear(); // clear the old list	 
	 curProjectiles.assign(newList.begin(), newList.end()); // set it to the new list
      }
      //std::cout << "size of p list : " << curProjectiles.size() << std::endl;
   }
   
   bool inBound() {
      if ((current.x > 640) ||
	  (current.x < 0) ||
	  (current.y > 480) ||
	  (current.y < 0))
	 return false;
      return true;      
   }
      
   
};

#endif
