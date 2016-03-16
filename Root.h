/**
 * @file Root.h
 * @brief
 *
 * @author
 * @bug
 */

#ifndef ROOT_H
#define ROOT_H

#include "Drawable.h"
#include "Updateable.h"
#include "Controls.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Player.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <list>
#include <iostream>

using std::shared_ptr;
using std::make_shared;
using std::list;

class Root : public Drawable, public Updateable, public Controls {
  private:
   //int fps;
   
   
  public:
   // root is initialized with some integer p (1 or 2), which represents the game mode
   // ie. 1 - single player; 2 - multi player
   // addPlay takes care of this setup process and assigns a key configuration for each
   // player depending on the mode selected
   int fps;
   Root(int frames) {
      fps = frames;
   }
   
   // game setup
   //virtual void setup() = 0;
   
   // with this new structure we need to make sure that whenever something is added (Player,
   // Enemy, Projectile, etc.) it is done through the Root class.  This means using some kind
   // of flag (bool, int, etc. ) inside the object classes to signal that a change needs to
   // occur from root

   // virtuals
   virtual bool is_game_over() = 0;
   //virtual void update(double) = 0;
   //virtual void draw() = 0;
   //virtual void updatePlayer() = 0;
   virtual void collision() = 0;
   virtual void clean() = 0;
   virtual void updateScore(ALLEGRO_COLOR) = 0;
   //virtual void set(int) = 0;
   //virtual void reset(int) = 0;
};

#endif
