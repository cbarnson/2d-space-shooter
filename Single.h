/**
 * @file Single.h
 * @brief Declaration of Single class
 *
 * @author
 * @bug
 */
#ifndef SINGLE_H
#define SINGLE_H

#include "Root.h"
#include "Background.h"
#include "Projectile.h"
#include "Laser.h"
#include "Missile.h"
#include "Player.h"
#include "Enemy.h"
#include "Sprite.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <list>
#include <memory>
#include <iostream>
#include <string>

using std::cout;
using std::list;
using std::shared_ptr;
using std::make_shared;

/**
 * @class Single
 */
class Single : public Root {
  public:   
  Single(int frames) : Root(frames) {
      load_assets();
   }
   
   ~Single();

   // game setup
   void load_assets();
   
   // virtuals from root
   void update(double);
   void draw();   
   void input(const ALLEGRO_EVENT&);
   
   bool is_game_over();
   void updateScore(ALLEGRO_COLOR);
   void spawn();

   
  private:
   ALLEGRO_FONT* gameOverFont;
   ALLEGRO_TIMER* gameOverTimer;
   
   list< shared_ptr<Projectile> > proj;
   list< shared_ptr<Enemy> > enem;
   list< shared_ptr<Player> > play;
   shared_ptr<Background> bg;

   // HELPER FUNCTIONS - simplicity & readability
   void drawPlayer();
   void drawProjectiles();
   void drawEnemies();
   void drawBackground();
   void updatePlayerPosition(double);
   void updateProjectilePosition(double);
   void updateEnemyPosition(double);
   void updateBackgroundPosition(double);
   void setupPlayer();
   void setupBackground();
   void cullPlayer();
   void cullProjectiles();
   void cullEnemies();
   void updatePlayerAction();
   void collision();
   void clean();
   void showGameOverMessage();

};

#endif
