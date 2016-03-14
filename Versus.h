#ifndef VERSUS_H
#define VERSUS_H

#include "Root.h"
#include "Projectile.h"
#include "Player.h"
#include "Enemy.h"


class Versus : public Root {

  private:
   list< shared_ptr<Projectile> > proj;
   list< shared_ptr<Enemy> > enem;
   list< shared_ptr<Player> > play;
   bool game_over;

  public:
  Versus(int frames) : Root(frames)
   {
      game_over = false;
   }   
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
