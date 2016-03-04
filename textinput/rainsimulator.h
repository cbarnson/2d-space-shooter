//////////////////////////////////////////////////////////////////////////////////
/* Josh Mohan
/ CPSC 2720- Assignment 1
/ Feb 23, 2016
/ RAINSIMULATOR: Although named rain simulator, it is actually the derived 
/               simulator for both animations.
/
///////////////////////////////////////////////////////////////////////////////*/

#ifndef RAINSIMULATOR_H
#define RAINSIMULATOR_H
#include "Simulator.h"
#include "Triangle.h"
//#include "Tree.h"
#include <allegro5/allegro_primitives.h>
#include <memory>
#include <list>

class rainsimulator: public Simulator {
  private:
   int width, height;
   list<shared_ptr<Drawable>> toDraw;//list to contain drawable objects
   list<shared_ptr<Updatable>> toMove;//list to contain updatable objects
   
  public:
   rainsimulator(const Display& d, int fps ): Simulator(d, fps){width=d.getW(); height=d.getH();}
   void addDrawable(shared_ptr<Drawable> d){
      toDraw.push_back(d);}//puts drawable items on list

   void addMovable(shared_ptr<Updatable> p){
      toMove.push_back(p);}//puts updatable items on list

   /*
     iterates through list of updatable objects, pushes them to respective move functions
    */
   void updateModel(double dt){
      list<shared_ptr<Updatable>>::iterator it;
      for(it= toMove.begin(); it!= toMove.end(); ++it)
      {
	 (*it)->move(dt);
	 }
   }
   /*
     iterates through list of drawable objects, pushes them to respective draw functions
    */
   void drawModel(){
      list<shared_ptr<Drawable>>::iterator it;
      al_clear_to_color(al_map_rgb(0,0,0));
      for(it=toDraw.begin(); it!=toDraw.end(); ++it)
      {
	 (*it)->draw();
      }
      al_flip_display();

   }
 
  
   
};

#endif
