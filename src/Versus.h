#ifndef VERSUS_H
#define VERSUS_H

#include "Root.h"

#include <memory>
#include <vector>

#include <allegro5/allegro.h>

#include "Vector.h"
#include "Point.h"

class Projectile;
class Background;
class Sprite;
class Player;
class Font;
class Timer;

// externals
extern const int GAME_OVER_DELAY;
extern const int RESPAWN_DELAY;
extern const int WEAPON_DELAY_LASER_VERSUS;
extern const int WEAPON_DELAY_MISSILE_VERSUS;
extern const Vector PLAYER1_PROJECTILE_SPEED;
extern const Vector PLAYER2_PROJECTILE_SPEED;

class Versus : public Root {
  public:
   Versus(int w, int h, int f); // uses the Root constructor
   ~Versus();

   // inherited from Root
   void draw();
   void update(double dt);
   // pure virtuals from Root
   void init();
   void input(ALLEGRO_KEYBOARD_STATE&);
   void updateScore(ALLEGRO_COLOR&);
   bool is_game_over();
   int getScore() const;
   
  private:
   // general game information
   int _score1;
   int _score2;
   int _life1;
   int _life2;
   bool _gameOver; // signals game mode Versus should end
   // timers
   std::shared_ptr<Timer> _player1WeaponTimer;
   std::shared_ptr<Timer> _player2WeaponTimer;
   std::shared_ptr<Timer> _gameOverTimer;
   std::shared_ptr<Timer> _respawnTimer;
   std::shared_ptr<Timer> _respawnTimer2;
   // fonts
   std::shared_ptr<Font> _font18; // size 18 font
   // background
   std::shared_ptr<Background> _bg;
   // players
   std::shared_ptr<Player> _player1; // green player
   std::shared_ptr<Player> _player2; // red player
   // vector of projectiles
   std::vector< std::shared_ptr<Projectile> > _proj;
   // sprites
   std::shared_ptr<Sprite> _playerShip; // uss for both players
   
   // add functions for game entities
   void addPlayer(int p); // p = 1 for player 1, p = 2 for player 2   
   void addLaser(const Point&, const ALLEGRO_COLOR&, const Vector&);
   void addMissile(const Point&, const ALLEGRO_COLOR&, const Vector&);
   // draw functions for components
   void drawProjectiles();
   void drawLifeRemaining(int p); // lifes for each player in top corners
   void drawPlayers();
   void drawScore(int p);
   void drawGameOver();
   // update functions for components
   void updateProjectiles(double dt);
   void updateCollision();
   void updateCollisionPlayer1();
   void updateCollisionPlayer2();
   void updatePlayerStatus();
   // utility functions
   bool doColorsMatch(const ALLEGRO_COLOR&, const ALLEGRO_COLOR&);
   bool pointBoxCollision(const Point&, const Point&, const int&);
   void respawn(int p);
   void clean();
};




#endif 
