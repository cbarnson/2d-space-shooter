/** @file Menu.h
 * @brief Declaration of Menu class
 *
 * @author Cody Barnson
 */
 
#ifndef MENU_H
#define MENU_H

#include <memory>

#include "State.h"

#include <allegro5/allegro.h>
class Sprite;/**< forward declaration of Sprite class */
class Timer;/**< forward declaration of Timer class */

extern const int MENU_ANIMATION_DELAY;

class Menu {
  public:
   Menu(int fps);
   ~Menu();
   
   void init();/**< initializes resources- loads titlescreen image */
   void draw();/**< draws menu */
   bool animation();/**< function to handle timing of menu animation */

   void handleEvent(const ALLEGRO_EVENT&, gs::state&);/**<chooses whether to load or exit game */
   void handleKey(const ALLEGRO_KEYBOARD_STATE&, gs::state&);

  private:
   int _fps;
   int _mAnim;
   std::shared_ptr<Timer> _timer;
   std::shared_ptr<Sprite> _splash;
   
};

#endif 
