/**
 * @file Versus.h
 * @brief Declaration of Versus class
 *
 * @author
 * @bug
 */
#ifndef VERSUS_H
#define VERSUS_H

#include "Root.h"
#include "Projectile.h"
#include "Player.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <vector>
#include <list>

using std::vector;
using std::list;

class Versus : public Root {
   list< shared_ptr<Projectile> > proj;
   list< shared_ptr<Player> > play;
   
  public:
  Versus(int f, int w, int h) : Root(f, w, h) {
      setup();
   }
   ~Versus();
   
   void setup(); // has its own setup
   
   // virtuals   
   void update(double);
   void draw();
   
   bool is_game_over();
   void updateScore(const ALLEGRO_COLOR&);
   void input(const ALLEGRO_EVENT&);

  private:
   void updatePlayerAction();
   void updatePlayerPosition(double dt);
   void updateProjectilePosition(double dt);
   void collision();
   void clean();
   void cullPlayers();
   void cullProjectiles();

};


#endif
