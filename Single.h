#ifndef SINGLE_H
#define SINGLE_H

#include "Root.h"
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <list>
#include <memory>
#include <iostream>


using std::cout;
using std::list;

class Single : public Root {

  private:
   list< shared_ptr<Projectile> > proj;
   list< shared_ptr<Enemy> > enem;
   list< shared_ptr<Player> > play;
   //int fps;


   
  public:


   
  Single(int frames) : Root(frames) {
      cout << "setting up single\n";      
      setup();
      cout << "setup completed in single\n";
   }
   /*
   Single(int frames) {
      fps = frames;
      setup();
   }
   */

   
   // Single now has all public function of Root

   void setup(); // has its own setup
   
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
