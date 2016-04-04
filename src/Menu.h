#ifndef MENU_H
#define MENU_H

#include <memory>
#include <allegro5/allegro.h>
class Sprite;

class Menu {
  public:
   Menu(int fps);

   void init();
   void draw();
   bool animation();

  private:
   int framesPerSec;
   ALLEGRO_TIMER* timer;
   std::shared_ptr<Sprite> splash;
   int mAnim;
   
};

#endif 
