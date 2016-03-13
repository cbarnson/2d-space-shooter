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

#include <memory>
#include <list>
#include <iostream>


using std::shared_ptr;
using std::make_shared;
using std::list;

class Root : public Drawable, public Updateable, public Controls {
   
  private:
   list< shared_ptr<Projectile> > proj;
   list< shared_ptr<Enemy> > enem;
   list< shared_ptr<Player> > play;
   int fps;
   //bool single;
      
  public:
   // root is initialized with some integer p (1 or 2), which represents the game mode
   // ie. 1 - single player; 2 - multi player
   // addPlay takes care of this setup process and assigns a key configuration for each
   // player depending on the mode selected
  Root(int p, int frames) : fps(frames)
   {
      for (int i = 1; i <= p; i++)
	 addPlay(i);
   }

   // game setup
   void addPlay(int);

   // with this new structure we need to make sure that whenever something is added (Player,
   // Enemy, Projectile, etc.) it is done through the Root class.  This means using some kind
   // of flag (bool, int, etc. ) inside the object classes to signal that a change needs to
   // occur from root
   void addProj(shared_ptr<Projectile>);
   void addEnem(shared_ptr<Enemy>);

   
   void spawn();
   // virtuals
   void update(double);
   void draw();
   void updatePlayer();
   void collision();
   void clean();
   void set(int);
   void reset(int);
};

#endif
