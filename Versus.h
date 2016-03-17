#ifndef VERSUS_H
#define VERSUS_H

#include "Root.h"
#include "Projectile.h"
#include "Laser.h"
#include "Player.h"
//#include "Enemy.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <list>

using std::vector;
using std::list;

class Versus : public Root {
  private:
   list< shared_ptr<Projectile> > proj;
   list< shared_ptr<Player> > play;

  public:

  Versus(int frames) : Root(frames) {
      setup();
   }
   ~Versus();
   
   void setup(); // has its own setup
   
   // virtuals
   
   void update(double);
   void draw();
   void updatePlayer();
   void set(int);
   void reset(int);
   
   bool is_game_over();
   void collision();
   void clean();
   void updateScore(ALLEGRO_COLOR);

};


#endif
