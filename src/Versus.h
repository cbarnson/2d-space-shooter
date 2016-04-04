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

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <vector>
#include <list>

class Projectile;
class Player;
class Background;

class Versus : public Root {
  ALLEGRO_TIMER* gameOverTimer;
  ALLEGRO_FONT* gameOverFont;
  std::list< std::shared_ptr<Projectile> > proj;
  std::shared_ptr<Player> player1;
  std::shared_ptr<Player> player2;
  std::shared_ptr<Background> bg;

 public:
 Versus(int f, int w, int h) : Root(f, w, h) {
    load_assets();
  }

  ~Versus();
   
  void load_assets(); // has its own setup
   
  // virtuals   
  void update(double);
  void draw();
   
  bool is_game_over();
  void updateScore(ALLEGRO_COLOR&);
  void input(ALLEGRO_EVENT&);

 private:
  void updatePlayerAction();
  void updatePlayerPosition(double dt);
  void updateProjectilePosition(double dt);
  void collision();
  void clean();
  void cullPlayers();
  void cullProjectiles();
  void setupBackground();

};


#endif
