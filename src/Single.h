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
#include <vector>
#include <memory>
#include <string>

#include "Root.h"
#include "Vector.h"
#include "Background.h"
#include "Score.h"

// forward declarations
struct Point;
class Timer;
class Projectile;
class Enemy;
class Player;
class Sprite;
class Font;

/**
 * @class Single
 */

extern const int GAME_OVER_WAIT_TIME;
extern const int WEAPON_DELAY_LASER;
extern const int WEAPON_DELAY_MISSILE;
extern const Vector PLAYER_PROJECTILE_SPEED;

class Single : public Root {
   // high score
   std::shared_ptr<Score> _highscores;
   // fonts
   std::shared_ptr<Font> gameOverFont;
   std::shared_ptr<Font> gameScoreFont;   
   // timers
   std::shared_ptr<Timer> gameOverTimer;
   std::shared_ptr<Timer> playerWeapon1;
   std::shared_ptr<Timer> playerWeapon2;
   std::shared_ptr<Timer> playerRespawn;
   std::shared_ptr<Timer> upgradeText;
   std::shared_ptr<Timer> bossTime;

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
   std::shared_ptr<Sprite> enemyBomb;

   std::string _playerName;
   bool gameOver;
   bool _Boss=false; bool killedBoss;//dont think i use this currently
   int playerLives;
   int playerScoreTotal;
   int playerScore;
   bool writeComplete = false;
   bool bossFirstShot=false;

  public:
   // Single has public access to fps, displayWidth, and displayHeight
   Single(int w, int h, int f, std::string playerName);
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
   void addCreepMis(const Point&, Point, Point, Point, Point, const ALLEGRO_COLOR&, const Vector&);
   
   void input(ALLEGRO_KEYBOARD_STATE&);   
   bool is_game_over();
   void updateScore(ALLEGRO_COLOR&);
   int getScore() const;
      
   void spawn();
   void respawnPlayer();

   void bossIntro();
   void spawnBoss();
   void bossFire(std::shared_ptr<Enemy>);
  private:   
   // HELPER FUNCTIONS - simplicity & readability
   void drawLives();
   void drawWeaponUpgradeStatus();
   void drawProjectiles();
   void drawEnemies();

   void updateProjectilePosition(double);
   void updateEnemyPosition(double);
   void updateHighscores();
   
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
   bool bossFlag();
   bool doHitboxesIntersect(const Point&, const int&,
			    const Point&, const int&);   
   bool doColorsMatch(const ALLEGRO_COLOR&, const ALLEGRO_COLOR&);
   bool isPointBoxCollision(const Point&, const Point&, const int&);

};

#endif
