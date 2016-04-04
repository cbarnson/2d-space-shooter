/**
 * @file Simulator.h
 * @brief Declaration of Simulator class
 *
 * @author
 * @bug
 */
#ifndef __SIMULATOR_H
#define __SIMULATOR_H

#include "Display.h"
#include <allegro5/allegro.h>

/**
 * @class Simulator
 * @brief Handles setup of the Allegro library for animation, a timer to control
 *        rendering, a common Allegro event queue, and a game loop
 */
class Simulator {   
  public:    
   /**
    * @fn Simulator(const Display& d, int fps)
    * @brief takes Display object d, and specified fps; initializes Allegro library
    */
   Simulator(const Display & d, int fps);
   ~Simulator();	

   /**
    * @fn run()
    * @brief Runs the main game loop
    */
   void run();
   
   virtual bool is_game_over() = 0;
   virtual void reset_game() = 0;
   virtual void menuMessage() = 0;
   virtual void single_player() = 0;
   virtual void multi_player() = 0;

   virtual void updateRoot(double dt) = 0;
   virtual void drawRoot() = 0;
   virtual void getInput(const ALLEGRO_EVENT&) = 0;
   virtual bool gameReady()=0;

   
  private:
   int framesPerSec; /// the rendering frequency
   ALLEGRO_TIMER *timer;  /// generates events for the simulation
   ALLEGRO_EVENT_QUEUE *eventQueue;  /// event storage 	

};

#endif
