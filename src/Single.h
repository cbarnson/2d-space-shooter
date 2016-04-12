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

// forward declaring classes is preferable to include "....h" in headers
struct Point;
struct Vector;
class Timer;
class Projectile;
class Enemy;
class Player;
class Background;
class Sprite;
class Font;

/**
 * @class Single
 */

extern const int WEAPON_DELAY_LASER;
extern const int WEAPON_DELAY_MISSILE;

class Single : public Root {

   // fonts
   std::shared_ptr<Font> gameOverFont;
   std::shared_ptr<Font> gameScoreFont;
   
   // timers
   std::shared_ptr<Timer> gameOverTimer;
   std::shared_ptr<Timer> playerWeapon1;
   std::shared_ptr<Timer> playerWeapon2;
   std::shared_ptr<Timer> playerRespawn;
   std::shared_ptr<Timer> upgradeText;   

   // base classes
   std::list< std::shared_ptr<Projectile> > proj;
   std::list< std::shared_ptr<Enemy> > enem;   
   std::shared_ptr<Player> player;

   // background
   std::shared_ptr<Background> bg;

   // sprites
   std::shared_ptr<Sprite> playerShip;
   std::shared_ptr<Sprite> enemyShip;
   std::shared_ptr<Sprite> enemyDeath;
   std::shared_ptr<Sprite> bossShip;

   bool gameOver;
   bool aliveBoss = false;
   int playerLives;
   int playerScoreTotal;
   int playerScore;

  public:
   // Single has public access to fps, displayWidth, and displayHeight
   Single(int w, int h, int f);
   ~Single();

   void shutdown();
   void init();
   
   // virtuals from root
   void update(double);
   void draw();

   void addLaser(const Point&, const ALLEGRO_COLOR&, const Vector&);
   void addMissile(const Point&, const ALLEGRO_COLOR&, const Vector&);
   void addCreepB(const Point&, const ALLEGRO_COLOR&, const Vector&);
   void addCreep(const Point&, const ALLEGRO_COLOR&, const Vector&);
   void addBoss(const Point&, const ALLEGRO_COLOR&, const Vector&);
   
   void input(ALLEGRO_KEYBOARD_STATE&);   
   bool is_game_over() const;
   void updateScore(ALLEGRO_COLOR&);
   
   void spawn();
   void respawnPlayer();
   void spawnBoss();
   
  private:   
   // HELPER FUNCTIONS - simplicity & readability
   void drawLives();
   
   void drawProjectiles();
   void drawEnemies();

   void updateProjectilePosition(double);
   void updateEnemyPosition(double);
   
   void setupPlayer();
   
   void cullPlayer();
   void cullProjectiles();
   void cullEnemies();
   void CircleLaser(std::shared_ptr<Enemy>);
   void clean();
   void showGameOverMessage();
   
   void collision();
   void checkCollisionOnPlayer();
   void checkCollisionOnEnemies();
   void checkCollidingEnemyWithPlayer();
   
   bool doHitboxesIntersect(const Point&, const int&,
			    const Point&, const int&);   
   bool doColorsMatch(const ALLEGRO_COLOR&, const ALLEGRO_COLOR&);
   bool isPointBoxCollision(const Point&, const Point&, const int&);

};

#endif
