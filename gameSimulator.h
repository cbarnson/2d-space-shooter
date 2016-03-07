/**
 * @file mySimulator.h
 * @brief definition of the mySimulator class
 *
 * This class inherits the public members of the Simulator class
 * 
 * @author Cody Barnson
 * @bug no known bugs
 */

#ifndef __GAMESIMULATOR_H
#define __GAMESIMULATOR_H

#include "Simulator.h"
#include "Drawable.h"
#include "Updateable.h"
#include "Controls.h"
#include <allegro5/allegro_primitives.h>
#include <list>
#include <vector>
#include <memory>

class gameSimulator : public Simulator {
  private:
   std::list< std::shared_ptr<Drawable> > toDraw;
   std::list< std::shared_ptr<Updateable> > toUpdate;
   std::list< std::shared_ptr<Controls> > playerControls; // not really any reason to have as
                                                          // list.. will change later
   int displayWidth, displayHeight;
   
  public:
  gameSimulator(const Display& d, int fps) : Simulator(d, fps) {
      displayWidth = d.getW();
      displayHeight = d.getH();
   }
   
   void addDrawable(std::shared_ptr<Drawable> p) {
      toDraw.push_back(p);
   }
   void addUpdateable(std::shared_ptr<Updateable> p) {
      toUpdate.push_back(p);
   }
   void addPlayer(std::shared_ptr<Controls> p) {
      playerControls.push_back(p);
   }

   
   void setPlayer(int code) {
      for (std::list< std::shared_ptr<Controls> >::iterator it = playerControls.begin();
	   it != playerControls.end(); ++it) 
	 (*it)->set(code);
   }
   void resetPlayer(int code) {
      for (std::list< std::shared_ptr<Controls> >::iterator it = playerControls.begin();
	   it != playerControls.end(); ++it) 
	 (*it)->reset(code);
   }

   
   // updates the vector for the player's speed/direction
   void updatePlayerControls() {
      for (std::list< std::shared_ptr<Controls> >::iterator it = playerControls.begin();
	   it != playerControls.end(); ++it) 
	 (*it)->updatePlayer();
   }

   // updates the position for the player's ship
   void updateModel(double dt) {
      for (std::list<std::shared_ptr<Updateable>>::iterator it = toUpdate.begin();
	   it != toUpdate.end(); ++it) {	 
	 (*it)->update(dt);
      }
   }

   // actually draws the model after each update
   void drawModel() {
      al_clear_to_color(al_map_rgb(0,0,0));      
      for (std::list<std::shared_ptr<Drawable>>::iterator it = toDraw.begin();
	   it != toDraw.end(); ++it)
	 (*it)->draw();
      al_flip_display();	    
   }
};

#endif

