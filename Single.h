#ifndef SINGLE_H
#define SINGLE_H

#include "Root.h"
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"
#include "Sprite.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <list>
#include <memory>
#include <iostream>
//#include <ctime>
//#include <cstdlib>

using std::cout;
using std::list;


class Single : public Root {

  private:
   list< shared_ptr<Projectile> > proj;
   list< shared_ptr<Enemy> > enem;
   list< shared_ptr<Player> > play;
   //int fps;
   //Sprite *map1;
   
   
  public:
   
  Single(int frames) : Root(frames) {
      //cout << "setting up single\n";      
      setup();
      //load_assets();
      //cout << "setup completed in single\n";
   }
   ~Single();
   
   
   // Single now has all public function of Root

   void setup(); // has its own setup
   void load_assets();
   
   // virtuals from Root
   bool is_game_over();
   void collision();
   void clean();
   void updateScore(ALLEGRO_COLOR);

   // virtuals from others
   void update(double);
   void draw();
   void updatePlayer();
   void set(int);
   void reset(int);
   void spawn();

};

#endif
