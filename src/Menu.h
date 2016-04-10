#ifndef MENU_H
#define MENU_H

#include <memory>
#include <allegro5/allegro.h>
#include "State.h"

class Sprite;
class Timer;

extern const int MENU_ANIMATION_DELAY;

class Menu {
  public:
   Menu(int fps);
   ~Menu();
   
   void init();
   void draw();
   bool animation();

   void handleEvent(const ALLEGRO_EVENT&, gs::state&);
   void handleKey(const ALLEGRO_KEYBOARD_STATE&, gs::state&);

  private:
   int _fps;
   int _mAnim;
   std::shared_ptr<Timer> _timer;
   std::shared_ptr<Sprite> _splash;
   
};

#endif 
