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
#include <string>

#include "State.h"
// forward declarations
class Menu;
class Root;

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

   inline void setName(std::string playerName) {
      _playerName = playerName;
   }   
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
   // general game variables
   int _displayWidth;
   int _displayHeight;
   int _fps;
   int _gameScore;
   std::string _playerName;   
   gs::state _state;
   // allegro objects
   ALLEGRO_TIMER *_timer;
   ALLEGRO_EVENT_QUEUE *_eventQueue;
   ALLEGRO_DISPLAY *_display;
   // menu scene
   std::shared_ptr<Menu> _menu;
   // root designates game mode - single or versus
   std::shared_ptr<Root> _root; 

   // functions to add components
   void addSingle();
   void addVersus();
   void addMenu();
};





#endif
