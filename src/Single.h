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
//#include "Root.h"

// forward declaring classes is preferable to include "....h" in headers
struct Point;
struct Vector;
class Timer;
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
   ALLEGRO_FONT* gameScoreFont;
   //ALLEGRO_TIMER* gameOverTimer;
   
   // some player action timers
   //ALLEGRO_TIMER* playerWeapon1;
   //ALLEGRO_TIMER* playerWeapon2;
   //ALLEGRO_TIMER* upgradeText;

   // respawn timer
   //ALLEGRO_TIMER* playerRespawn;

   std::shared_ptr<Timer> gameOverTimer;
   std::shared_ptr<Timer> playerWeapon1;
   std::shared_ptr<Timer> playerWeapon2;
   std::shared_ptr<Timer> playerRespawn;
   std::shared_ptr<Timer> upgradeText;   

   std::list< std::shared_ptr<Projectile> > proj;
   std::list< std::shared_ptr<Enemy> > enem;
   std::shared_ptr<Player> player;
   std::shared_ptr<Sprite> playerShip;
   std::shared_ptr<Background> bg;

   bool gameOver;
   int playerLives;
   int playerScore;

  public:
   // Single has public access to fps, displayWidth, and displayHeight
   Single(int w, int h, int f);
   /*
  Single(int w, int h, int f) : Root(w, h, f),
      gameOver(false),
      playerLives(3),
      playerScore(0)
      {
	 load_assets();
      }
   */
   ~Single();

   void shutdown();
   // game setup
   void init();
   
   // virtuals from root
   void update(double);
   void draw();

   void addLaser(const Point&, const ALLEGRO_COLOR&, const Vector&);
   void addMissile(Point cen, ALLEGRO_COLOR col, Vector spd);

   //void input(ALLEGRO_EVENT&);   
   void input(ALLEGRO_KEYBOARD_STATE&);   
   bool is_game_over();
   void updateScore(ALLEGRO_COLOR&);
   void spawn();

   void respawnPlayer();
   
  private:   
   // HELPER FUNCTIONS - simplicity & readability
   void drawLives();
   void drawScore();
   
   void drawProjectiles();
   void drawEnemies();
   void drawBackground();
   //void drawWeaponUp();
   void updateProjectilePosition(double);
   void updateEnemyPosition(double);
   void updateBackgroundPosition(double);
   void setupPlayer();
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
