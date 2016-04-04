/**
 * @file Single.h
 * @brief Declaration of Single class
 *
 * @author
 * @bug
 */
#ifndef SINGLE_H
#define SINGLE_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <list>
#include <memory>
#include "Root.h"

// forward declaring classes is preferable to include "....h" in headers
struct Point;
class Projectile;
class Enemy;
class Player;
class Background;
class Sprite;

/**
 * @class Single
 */
class Single : public Root {
   // important private members
   ALLEGRO_FONT* gameOverFont;
   ALLEGRO_TIMER* gameOverTimer;
   
   // some player action timers
   ALLEGRO_TIMER* playerWeapon1;
   ALLEGRO_TIMER* playerWeapon2;

   std::list< std::shared_ptr<Projectile> > proj;
   std::list< std::shared_ptr<Enemy> > enem;
   std::shared_ptr<Player> player;
   std::shared_ptr<Sprite> playerShip;
   std::shared_ptr<Background> bg;

  public:
   // Single has public access to fps, displayWidth, and displayHeight
 Single(int w, int h, int f) : Root(w, h, f) {
      load_assets();
   }
   
   ~Single();
   
   // game setup
   void load_assets();
   
   // virtuals from root
   void update(double);
   void draw();   

   //void input(ALLEGRO_EVENT&);   
   void input(ALLEGRO_KEYBOARD_STATE&);   
   bool is_game_over();
   void updateScore(ALLEGRO_COLOR&);
   void spawn();

   
  private:   
   // HELPER FUNCTIONS - simplicity & readability
   void drawProjectiles();
   void drawEnemies();
   void drawBackground();
   void updateProjectilePosition(double);
   void updateEnemyPosition(double);
   void updateBackgroundPosition(double);
   void setupPlayer();
   void setupBackground();
   void cullPlayer();
   void cullProjectiles();
   void cullEnemies();
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
