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
<<<<<<< HEAD
#include <iostream>
=======
#include <iostream>//for testing, remove later
>>>>>>> a800d4ddb56872166ca8bb047b962c4930685cce
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
   list< shared_ptr<Player> > otherPlayers;
   //shared_ptr<Player> player2;
   
   Point current;       // ship position
   ALLEGRO_COLOR color; // ship color
   Hotkeys config;      // key mapping profile
   bool flipped;
   int addPlayers;
   
   bool live;
   Vector speed;        // movement speed in any direction
   Vector projSpeed;    // speed of projectiles
   int xModifier;       // x movement speed
   int yModifier;       // y movement speed
   int size;            // ship size in pixels
   
  public:
   //list< shared_ptr<Projectile> > curProjectiles;
   //list< shared_ptr<Enemy> > curEnemies;
   //list< shared_ptr<Player> > otherPlayers;

  Player(Point p, ALLEGRO_COLOR c, vector<int> h, bool f, int a) : current(p),
      color(c), config(h), flipped(f)
   {
      //otherPlayers.push_back(op);
      speed = Vector(0, 0);      
      xModifier = 150;
      yModifier = 150;
      live = true;
      //boundx =

      // add other players here
      switch (a) {
	 case 1: // add one player
	    vector<int> h2;
	    h2.push_back(ALLEGRO_KEY_W);
	    h2.push_back(ALLEGRO_KEY_S);
	    h2.push_back(ALLEGRO_KEY_D);
	    h2.push_back(ALLEGRO_KEY_A);
	    h2.push_back(ALLEGRO_KEY_SPACE);
	    otherPlayers.push_back(make_shared<Player> (Point(400, 240),
							al_map_rgb(255,0,0), h2, false, 0));
	    break;
	    //default:
	    // break; // do nothing
      }
      if (flipped) {
	 size = 50;
	 projSpeed = Vector(200, 0);
      }
      else {
	 size = -50;
	 projSpeed = Vector(-200, 0);
      }
   }
   

   void setLive(bool l) { live = l; }
   Point getCurrent() { return current; }
   list< shared_ptr<Projectile> > getProj() { return curProjectiles; }   
   bool getLive() { return live; }

   //******************************************************************
   // called when ALLEGRO_EVENT_KEY_UP
   //******************************************************************
   void set(int code) {
      for (int i = 0; i < 5; i++) {
	 if (code == config.control[i])
	    config.keys[i] = true;
      }
      // OTHER PLAYERS
      if (!otherPlayers.empty()) {
	 for  (list< shared_ptr<Player> >::iterator it = otherPlayers.begin();
	       it != otherPlayers.end(); ++it) {
	    (*it)->set(code);
	 }
      }
   }

   //******************************************************************
   // called when ALLEGRO_EVENT_KEY_DOWN
   //******************************************************************
   void reset(int code) {
      for (int i = 0; i < 5; i++) {
	 if (code == config.control[i])
	     config.keys[i] = false;
      }

      // OTHER PLAYERS
      if (!otherPlayers.empty()) {
	 for  (list< shared_ptr<Player> >::iterator it = otherPlayers.begin();
	       it != otherPlayers.end(); ++it) {
	    (*it)->reset(code);
	 }
      }
   }   

   //******************************************************************
   // draws a side-ways triangle (representing the player ship
   // note: the first coordinate is the tip of the ship
   //******************************************************************
   void draw() {
<<<<<<< HEAD
      if (live) {
	 al_draw_filled_triangle(current.x, current.y,
				 current.x - size, current.y + 0.5 * size,
				 current.x - size, current.y - 0.5 * size,
				 color);
      }
      // OTHER PLAYERS
      if (!otherPlayers.empty()) {
	 for  (list< shared_ptr<Player> >::iterator it = otherPlayers.begin();
	       it != otherPlayers.end(); ++it) {
	    (*it)->draw();
	 }
      }
      
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
      
=======
       al_draw_filled_triangle(current.x, current.y,
			      current.x, current.y + size,
			      current.x + size, current.y + (size/2),
			      al_map_rgb(0,204,0));
      if(!curEnemies.empty())
      {
	 for(std::list<std::shared_ptr<Enemy>>::iterator it=curEnemies.begin(); it!=curEnemies.end(); ++it)
	 {
	    (*it)->draw();
	 }
      }
     
>>>>>>> a800d4ddb56872166ca8bb047b962c4930685cce
   }







   //******************************************************************
   // function to interpret key pressed into a move command or shoot command
   // I decided to change the function to accept 2 parameters, to allow the movements to be
   // completely independent of eachother
   //******************************************************************
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
      // OTHER PLAYERS
      if (!otherPlayers.empty()) {
	 for  (list< shared_ptr<Player> >::iterator it = otherPlayers.begin();
	       it != otherPlayers.end(); ++it) {
	    (*it)->updatePlayer();
	 }
      }
      
   }




   //******************************************************************
   // update handles all the position changes for all objects that are NOT the player
   //******************************************************************
   void update(double dt) {
      if (live) {
	 current = current + speed * dt;
	 speed = Vector(0, 0);
      
	 // check x bound
	 if (current.x > 800)
	    current.x = 800;
	 else if (current.x < size)
	    current.x = size;
	 // check y bound
	 if ((current.y + size * 0.5) > 600)
	    current.y = 600 - size * 0.5;
	 else if (current.y < size * 0.5)
	    current.y = size * 0.5;
      }
	 
      // OTHER PLAYERS
      if (!otherPlayers.empty()) {
	 for  (list< shared_ptr<Player> >::iterator it = otherPlayers.begin();
	       it != otherPlayers.end(); ++it) {
	    (*it)->update(dt);
	 }
      }
      
      // ENEMIES
      if (!curEnemies.empty()) {
	 for (list< shared_ptr<Enemy> >::iterator it = curEnemies.begin();
	      it != curEnemies.end(); ++it) {
	    (*it)->update(dt);
	 }
      }

      // PROJECTILES
      if (!curProjectiles.empty()) {	 
	 //list< shared_ptr<Projectile> > newList;	 
	 for (list< shared_ptr<Projectile> >::iterator it = curProjectiles.begin();
	      it != curProjectiles.end(); ++it) {	    
	    (*it)->update(dt);
	 }
	 
      }


      
      // COLLISION PLAYER 1 SHOTS, CHECKING FOR HITS ON PLAYER 2
      if (!otherPlayers.empty() && !curProjectiles.empty())  {
	    for (list< shared_ptr<Player> >::iterator i = otherPlayers.begin();
		 i != otherPlayers.end(); ++i) {
	       
	       if ((*i)->getLive()) {
		  
		  for (list< shared_ptr<Projectile> >::iterator j = curProjectiles.begin();
		       j != curProjectiles.end(); ++j) {
		     
		     if ((*j)->getLive()) {
			Point temp = (*i)->getCurrent();
			Point boundTopLeft = Point(temp.x, temp.y - (size * 0.5));
			Point boundBotRight = Point(temp.x + size, temp.y + (size * 0.5));
			Point shot = (*j)->getCenter();
			
			if ((shot.x > boundTopLeft.x) &&
			    (shot.x < boundBotRight.x) &&
			    (shot.y > boundTopLeft.y) &&
			    (shot.y < boundBotRight.y)) {
			   // hit
			   (*i)->setLive(false);
			   (*j)->setLive(false);
			   std::cout << "HIT ON ----PLAYER2-----" << std::endl;
			   break; // continue to the next player or exit the loop if no more
			}
		     }
		  }
	       }
	    }
	 }

      // COLLISION PLAYER 2 SHOTS, CHECKING FOR HITS ON PLAYER 1
      if (!otherPlayers.empty()) {

	 for (list< shared_ptr<Player> >::iterator p = otherPlayers.begin();
	      p != otherPlayers.end(); ++p) {
	    
	    if ((*p)->getLive() && !(*p)->curProjectiles.empty()) {

	       list< shared_ptr<Projectile> > proj((*p)->curProjectiles);
	       for (list< shared_ptr<Projectile> >::iterator i = proj.begin();
		    i != proj.end(); ++i) {
		  
		  if ((*i)->getLive()) {
		     
		     Point boundTopLeft = Point(current.x - size, current.y - (size * 0.5));
		     Point boundBotRight = Point(current.x, current.y + (size * 0.5));
		     Point shot = (*i)->getCenter();
		     
		     if ((shot.x > boundTopLeft.x) &&
			 (shot.x < boundBotRight.x) &&
			 (shot.y > boundTopLeft.y) &&
			 (shot.y < boundBotRight.y)) {
			// hit
			(*i)->setLive(false);
			setLive(false);
			std::cout << "HIT ON ----PLAYER1-----" << std::endl;
			break; // continue to the next player or exit the loop if no more
		     }
		  }		  
	       }
	    }
	 }	       
      }

      // CLEAR PLAYERS AND PROJECTILES FOR WHICH LIVE = FALSE
      list< shared_ptr<Projectile> > newList;	 
      for (list< shared_ptr<Projectile> >::iterator it = curProjectiles.begin();
	   it != curProjectiles.end(); ++it) {
	 if ((*it)->getLive()) 
	    newList.push_back(*it); 	    	    
      }
      curProjectiles.clear();	 
      curProjectiles.assign(newList.begin(), newList.end());       


      
      list< shared_ptr<Player> > newListPlayer;	       
      for (list< shared_ptr<Player> >::iterator it = otherPlayers.begin();
	   it != otherPlayers.end(); ++it) {
	 
	 if ((*it)->getLive()) {
	    newListPlayer.push_back(*it);

	    if (!(*it)->curProjectiles.empty()) {

	       list< shared_ptr<Projectile> > listPlayerProj((*it)->curProjectiles);
	       list< shared_ptr<Projectile> > newListPlayerProj;
	       for (list< shared_ptr<Projectile> >::iterator j = listPlayerProj.begin();
		    j != listPlayerProj.end(); ++j) {
		  
		  if ((*j)->getLive()) {
		     newListPlayerProj.push_back(*j);
		  }
	       }
	       (*it)->curProjectiles.clear();
	       (*it)->curProjectiles.assign(newListPlayerProj.begin(),
					    newListPlayerProj.end());
	    }
	 }
      }
<<<<<<< HEAD
      otherPlayers.clear();	 
      otherPlayers.assign(newListPlayer.begin(), newListPlayer.end());
=======
      
     
>>>>>>> a800d4ddb56872166ca8bb047b962c4930685cce
      

      
      
<<<<<<< HEAD
   }


   //******************************************************************
   // check if Player is within the boundaries
   //******************************************************************
   bool inBound() {
      if ((current.x > 640) ||
	  (current.x < 0) ||
	  (current.y > 480) ||
	  (current.y < 0))
	 return false;
      return true;      
   }
      
=======
      //code for handling enemy spawning
      //int numEnemies=curEnemies.size();

      if(curEnemies.size()<5)
      {//rand numbers just allow enemies to travel along different paths
	 std::shared_ptr<Enemy> en=std::make_shared<Enemy>(Point(800, rand()%600),
							   Point(0, rand()%600));
	 curEnemies.push_back(en);
      }
      if(!curEnemies.empty())
      {
	 for(std::list<std::shared_ptr<Enemy>>::iterator it=curEnemies.begin(); it!=curEnemies.end(); ++it)
	 {
	    (*it)->update(dt);
	 }
      }
      
  
   }
 
>>>>>>> a800d4ddb56872166ca8bb047b962c4930685cce
   
};

#endif
