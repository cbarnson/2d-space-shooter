#ifndef __SIMULATOR_H
#define __SIMULATOR_H

#include "Display.h"

/// Class responsible for setting up the Allegro library for some basic animation.
/**
   Initializes the Allegro timer that controls rendering, sets up a
   common Allegro event queue, and provides a rendering loop function for
   the animation.
**/
class Simulator {
  private:
   int framesPerSec; /// the rendering frequency
   ALLEGRO_TIMER *timer;  /// generates events for the simulation
   ALLEGRO_EVENT_QUEUE *eventQueue;  /// event storage 	

  public:
   /// The constructor initializes the Allegro library
   /**
      \param d the display object; needed so that the Simulator object
      recognizes when the "close window" button is pressed and the
      simulation needs to stop.
      \param fps the number of frames per second. This is the rate at
      which both the simulation and the rendering are performed.
   **/
   Simulator(const Display & d, int fps);
   ~Simulator();	

   void run();
   virtual bool is_game_over() = 0;
   virtual void menuMessage() = 0;
   virtual void single_player() = 0;
   virtual void multi_player() = 0;

   virtual void controlRoot() = 0;
   virtual void updateRoot(double dt) = 0;
   virtual void drawRoot() = 0;
   virtual void setRoot(int c) = 0;
   virtual void resetRoot(int c) = 0;
   virtual void collisionRoot() = 0;
};

#endif
