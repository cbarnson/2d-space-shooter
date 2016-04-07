/**
 * @file Root.h
 * @brief Declaration of Root class
 *
 * @author
 * @bug
 */

#ifndef ROOT_H
#define ROOT_H

#include "Drawable.h"
#include "Updateable.h"
#include <allegro5/allegro.h>

class Root : public Drawable, public Updateable {
  public:
   int displayWidth;
   int displayHeight;
   int framesPerSec;
   
 Root(int w, int h, int f) : displayWidth(w), displayHeight(h), framesPerSec(f)
   { }
   
   virtual ~Root() { }
   
   // virtuals
   void draw() { }
   void update(double dt) { }

   virtual void input(ALLEGRO_KEYBOARD_STATE&) = 0;   
   virtual bool is_game_over() const  = 0;
   virtual void updateScore(ALLEGRO_COLOR&) = 0;
};

#endif
