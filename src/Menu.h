#ifndef MENU_H
#define MENU_H

#include <memory>
#include <allegro5/allegro.h>
class Sprite;

class Menu {
  public:
   Menu();

   void init();
   void menuMessage();
   void menuAnim();

  private:
   ALLEGRO_TIMER* timer;
   std::shared_ptr<Sprite> splash;
   
};

#endif 
