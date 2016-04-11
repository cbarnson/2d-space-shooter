/** @file Menu.h
 * @brief Declaration of Menu class
 *
 * @author Cody Barnson
 */
 
#ifndef MENU_H
#define MENU_H

#include <memory>
#include <allegro5/allegro.h>
class Sprite;/**< forward declaration of Sprite class */
class Timer;/**< forward declaration of Timer class */

class Menu {
  public:
   Menu(int fps);
   ~Menu();
   
   void init();/**< initializes resources- loads titlescreen image */
   void draw();/**< draws menu */
   bool animation();/**< function to handle timing of menu animation */

  private:
   int framesPerSec;
   int mAnim;
   Timer* _timer;
   //ALLEGRO_TIMER* timer;
   std::shared_ptr<Sprite> splash;
   
};

#endif 
