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
#include "Player.h"
#include "Enemy.h"
#include "Point.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <list>
#include <memory>
#include <iostream>
#include <string>
#include <cmath>

using std::cout;
using std::list;
using std::shared_ptr;
using std::make_shared;

/**
 * @class Single
 */
class Single : public Root {
   // important private members
   ALLEGRO_FONT* gameOverFont;
   ALLEGRO_TIMER* gameOverTimer;
   
   list< shared_ptr<Projectile> > proj;
   list< shared_ptr<Enemy> > enem;
   list< shared_ptr<Player> > play;
   shared_ptr<Background> bg;

  public:
   // Single has public access to fps, displayWidth, and displayHeight
  Single(int f, int w, int h) : Root(f, w, h) {
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
   void updateScore(const ALLEGRO_COLOR&);
   void spawn();

   
  private:   
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
   void checkCollisionOnPlayer();
   void checkCollisionOnEnemies();
   void checkCollidingEnemyWithPlayer();
   
   bool doHitboxesIntersect(const Point&, const int&,
			    const Point&, const int&);
   bool doColorsMatch(const ALLEGRO_COLOR&, const ALLEGRO_COLOR&);
   bool isPointBoxCollision(const Point&, const Point&, const int&);

};

#endif
