/**
 * @file mySimulator.h
 * @brief definition of the mySimulator class
 *
 * This class inherits the public members of the Simulator class
 * 
 * @author Cody Barnson
 * @bug no known bugs
 */

#ifndef __MYSIMULATOR_H
#define __MYSIMULATOR_H

#include "Simulator.h"
#include "Drawable.h"
#include "Updateable.h"
#include <allegro5/allegro_primitives.h>
#include <list>
#include <memory>

/**
 * @class mySimulator
 * @brief contains lists of Drawable objects and Updateable objects and calls draw and update
 * for their dervived objects respectively
 */
class mySimulator : public Simulator {
  private:
   /**
    * @var toDraw
    * contains the list of objects to be created and displayed in the display window
    * @var toUpdate
    * contains the list of objects whose positions are to be updated
    */
   std::list<std::shared_ptr<Drawable>> toDraw;
   std::list<std::shared_ptr<Updateable>> toUpdate;


   /**
    * @var displayWidth
    * represents the maximum width of the display window
    * @var displayHeight
    * represents the maximum height of the display window
    */
   int displayWidth, displayHeight;
   
  public:
   
   /**
    * @fn mySimulator(d, fps)
    * @brief Constructor
    */   
  mySimulator(const Display& d, int fps) : Simulator(d, fps) {
      displayWidth = d.getW();
      displayHeight = d.getH();
   }

   
   /**
    * @fn void addDrawable(std::shared_ptr<Drawable> p)
    * @brief takes a smart pointer to Drawable object and pushes it onto the toDraw list
    * @param p the pointer to the Drawable object
    */
   void addDrawable(std::shared_ptr<Drawable> p) {
      toDraw.push_back(p);
   }


   /**
    * @fn void addUpdateable(std::shared_ptr<Updateable> p)
    * @brief takes a pointer to Updateable object and pushes it onto the to Update list
    * @param p the pointer to the Updateable object
    */
   void addUpdateable(std::shared_ptr<Updateable> p) {
      toUpdate.push_back(p);
   }


   /**
    * @fn void updateModel(double dt)
    * @brief takes some amount of time dt and calls each Updateable object's update function
    * @param dt the amount of time passed since the last update occurred 
    */
   void updateModel(double dt) {
      for (std::list<std::shared_ptr<Updateable>>::iterator it = toUpdate.begin();
	   it != toUpdate.end(); ++it)
	 (*it)->update(dt);
   }

   
   /**
    * @fn void drawModel()
    * @brief iteratively calls each Drawable object's draw function
    */
   void drawModel() {
      al_clear_to_color(al_map_rgb(0,0,0));      
      for (std::list<std::shared_ptr<Drawable>>::iterator it = toDraw.begin();
	   it != toDraw.end(); ++it)
	 (*it)->draw();
      al_flip_display();	    
   }
};

#endif

