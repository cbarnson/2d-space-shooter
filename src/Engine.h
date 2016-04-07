#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5/allegro.h>
#include <memory>
#include "State.h"

// forward declarations
class Menu;
class Root;
//class Timer;
using namespace gs;

class Engine {
   std::shared_ptr<Root> root;
   
  public:
   Engine(int w, int h, int fps);
   ~Engine();

   void init();
   void run();
   void draw();
   void update(double dt);
   void shutdown();
   void processGameLogic(float& prevTime, gs::state currentState);
   void menuLoop();
   void gameLoop(float& prevTime);

  private:
   int displayWidth;
   int displayHeight;
   int framesPerSec;
   //Timer* _timer;
   ALLEGRO_TIMER *_timer;
   ALLEGRO_EVENT_QUEUE *eventQueue;
   ALLEGRO_DISPLAY *display;


   bool running;
   gs::state gameState;
   Menu *gameMenu;
   
};





#endif
