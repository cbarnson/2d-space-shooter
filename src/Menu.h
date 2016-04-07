#ifndef MENU_H
#define MENU_H

#include <memory>
#include <allegro5/allegro.h>
class Sprite;
class Timer;

class Menu {
  public:
   Menu(int fps);
   ~Menu();
   
   void init();
   void draw();
   bool animation();

  private:
   int framesPerSec;
   int mAnim;
   Timer* _timer;
   //ALLEGRO_TIMER* timer;
   std::shared_ptr<Sprite> splash;
   
};

#endif 
