/**
 * @file Engine.h
 * @brief
 *
 * @author
 * @bug
 */
#ifndef ENGINE_H
#define ENGINE_H

#include <allegro5/allegro.h>
#include <memory>

#include "State.h"

// forward declarations
class Menu;
class Root;
using namespace gs;

class Engine {
      
  public:
   Engine(int w, int h, int fps);
   ~Engine();

   void init();
   void run();
   void draw();
   void update(double dt);
   void processGameLogic(float& prevTime, gs::state currentState);
   void menuLoop();
   void gameLoop(float& prevTime);

   void addSingle();
   void addMenu();
   
   inline int getWidth() const {
      return _displayWidth;
   }

   inline int getHeight() const {
      return _displayHeight;
   }

   inline int getFps() const {
      return _fps;
   }

  private:
   int _displayWidth;
   int _displayHeight;
   int _fps;
   int _gameScore; // initially -1
   ALLEGRO_TIMER *_timer;
   ALLEGRO_EVENT_QUEUE *_eventQueue;
   ALLEGRO_DISPLAY *_display;

   bool running;
   gs::state _state;
   std::shared_ptr<Menu> _menu;
   std::shared_ptr<Root> _root; // interface for game modes

     
};





#endif
