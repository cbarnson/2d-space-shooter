#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5/allegro.h>
#include "State.h"

class Input;

class Engine {
   std::shared_ptr<Root> root;
   std::shared_ptr<Sprite> menuPng;
   
  public:
   Engine(int w, int h, int fps);
   ~Engine();

   void init();
   void run();
   void draw();
   void update(double dt);
   bool menuLoop();
   void gameLoop();
   void shutdown();

   void menuMessage();

  private:
   ALLEGRO_DISPLAY *display;
   ALLEGRO_TIMER *timer;
   ALLEGRO_EVENT_QUEUE *eventQueue;
   int framesPerSec;
   int displayWidth;
   int displayHeight;

   bool running;
   state gameState;
   Input gameInput;
   
};





#endif
