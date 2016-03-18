#ifndef VERSUS_H
#define VERSUS_H

#include "Root.h"
#include "Projectile.h"
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
   //list< shared_ptr<Enemy> > enem;
   list< shared_ptr<Player> > play;
   //int fps;

  public:

  Versus(int frames) : Root(frames) {
      setup();
   }
   /*
   Versus(int frames) {
      fps = frames;
      setup();
      }
   */
   void setup(); // has its own setup
   
   // virtuals
   bool is_game_over();
   void update(double);
   void draw();
   void updatePlayer();
   void collision();
   void clean();
   void updateScore(ALLEGRO_COLOR);
   void set(int);
   void reset(int);

};


#endif
