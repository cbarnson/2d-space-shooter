#include "Versus.h"

#include <allegro5/allegro_primitives.h>

#include "Projectile.h"
#include "Laser.h"
#include "Missile.h"
#include "Timer.h"
#include "Background.h"
#include "Sprite.h"
#include "Player.h"
#include "Font.h"

const int GAME_OVER_DELAY = 80;
const int RESPAWN_DELAY = 50;
const int WEAPON_DELAY_LASER_VERSUS = 6;
const int WEAPON_DELAY_MISSILE_VERSUS = 20;
const Vector PLAYER1_PROJECTILE_SPEED = Vector(500, 0);
const Vector PLAYER2_PROJECTILE_SPEED = Vector(-500, 0);

Versus::Versus(int w, int h, int f) : Root(w, h, f)
{
   _score1 = 0;
   _score2 = 0;
   _life1 = 3;
   _life2 = 3;
   _gameOver = false;
}

Versus::~Versus() {
   _player1WeaponTimer.reset();
   _player2WeaponTimer.reset();
   _gameOverTimer.reset();
   _respawnTimer.reset();
   _font18.reset();
   _player1.reset();
   _player2.reset();
   _proj.clear();
   _playerShip.reset();
}

void Versus::init() {
   // timers - must call create() before using
   _player1WeaponTimer = std::make_shared<Timer> (framesPerSec);
   _player1WeaponTimer->create();
   _player1WeaponTimer->startTimer(); // start timer
   _player2WeaponTimer = std::make_shared<Timer> (framesPerSec);
   _player2WeaponTimer->create();
   _player2WeaponTimer->startTimer(); // start timer
   _gameOverTimer = std::make_shared<Timer> (framesPerSec);
   _gameOverTimer->create();
   _respawnTimer = std::make_shared<Timer> (framesPerSec);
   _respawnTimer->create();
   // create players
   addPlayer(1);
   addPlayer(2);
   // set path
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   // load sprites
   _playerShip = std::make_shared<Sprite> ("Sprite.png");
   // load fonts
   _font18 = std::make_shared<Font> ("ipag.ttf", 18); _font18->load();
   // load background
   _bg = std::make_shared<Background> (Vector(50, 0), Vector(-90, 0));
   // delete path
   al_destroy_path(path);
}

void Versus::draw() {
   // draw background
   _bg->draw();
   // draw each player's lives
   drawLifeRemaining(1);
   drawLifeRemaining(2);
   // draw players
   if (_player1) {
      _player1->draw(_playerShip, 0);
   }
   if (_player2) {
      _player2->draw(_playerShip, ALLEGRO_FLIP_HORIZONTAL);
   }
   // draw projectiles
   drawProjectiles();
   // draw game score
   drawScore(1);
   drawScore(2);
   // if game over draw game over message and results
   if (_gameOver) {
      drawGameOver();
   }
}



void Versus::update(double dt) {
   // update background
   _bg->update(dt);
   // update player position
   // player 1
   if (_player1) {
      _player1->update(dt);
   }
   else if (_life1 <= 0) {
      _gameOver = true;
   }
   else {
      respawn(1);
   }
   // player 2
   if (_player2) {
      _player2->update(dt);
   }
   else if (_life2 <= 0) {
      _gameOver = true;
   }
   else {
      respawn(2);
   }
   // update projectile positions
   updateProjectiles(dt);
   // update collisions
   updateCollision();
   // update status of players
   updatePlayerStatus();
}

void Versus::respawn(int p) {
   switch(p) {
      case 1: // respawn player 1
	 if (!_respawnTimer->isRunning()) {
	    _respawnTimer->startTimer();
	 }
	 else if (_respawnTimer->getCount() > 80) {
	    addPlayer(p);
	    _respawnTimer->stopTimer();
	    _respawnTimer->resetCount();
	 }
	 break;
	 
      case 2: // respawn player 2
	 if (!_respawnTimer->isRunning()) {
	    _respawnTimer->startTimer();
	 }
	 else if (_respawnTimer->getCount() > 80) {
	    addPlayer(p);
	    _respawnTimer->stopTimer();
	    _respawnTimer->resetCount();
	 }
	 break;
      default:
	 break;
   }
}


void Versus::input(ALLEGRO_KEYBOARD_STATE& kb) {
   // handle player 1
   if (_player1) {      
      switch(_player1->input(kb)) {
	 case act::action::QUIT_GAME:
	    _gameOver = true;
	    return;
	 case act::action::FIRE_PRIMARY:
	    if (_player1WeaponTimer->getCount() > WEAPON_DELAY_LASER_VERSUS) {
	       addLaser(_player1->centre, _player1->color, PLAYER1_PROJECTILE_SPEED);
	       _player1WeaponTimer->srsTimer(); // stop, reset, start
	    }
	    break;
	 case act::action::FIRE_SECONDARY:
	    // to be added
	    break;
	 default:
	    break;
      }
   }
   // handle player 2
   if (_player2) {
      switch(_player2->inputPlayer2(kb)) {
	 case act::action::QUIT_GAME:
	    _gameOver = true;
	    return;
	 case act::action::FIRE_PRIMARY:
	    if (_player2WeaponTimer->getCount() > WEAPON_DELAY_LASER_VERSUS) {
	       addLaser(_player2->centre, _player2->color, PLAYER2_PROJECTILE_SPEED);
	       _player2WeaponTimer->srsTimer();
	    }
	    break;
	 case act::action::FIRE_SECONDARY:
	    // to be added
	    break;
	 default:
	    break;
      }
   }
}
// pure virtual from Root
void Versus::updateScore(ALLEGRO_COLOR& color) {
   
}
// pure virtual from Root
bool Versus::is_game_over() const {
   return (_gameOverTimer->getCount() > GAME_OVER_DELAY) && _gameOver;
}
// pure virtual from Root
int Versus::getScore() const {
   return 0;
}

//================================
// ADD FUNCTIONS FOR COMPONENTS
//================================
void Versus::addPlayer(int p) {
   switch(p) {
      case 1:
	 _player1 = std::make_shared<Player> (Point(215, 245), al_map_rgb(0, 200, 0));
	 break;
      case 2:
	 _player2 = std::make_shared<Player> (Point(585, 245), al_map_rgb(200, 0, 0));
	 break;
      default:
	 break;
   }
}

// function to add a Laser object onto the Projectile list
void Versus::addLaser(const Point& cen, const ALLEGRO_COLOR& col, const Vector& spd) {
   _proj.push_back(std::make_shared<Laser> (cen, col, spd));
}

void Versus::addMissile(const Point& cen, const ALLEGRO_COLOR& col, const Vector& spd) {
   _proj.push_back(std::make_shared<Missile> (cen, col, spd));
}

//=============================
// DRAW FUNCTIONS FOR COMPONENTS
//==============================
void Versus::drawLifeRemaining(int p) {
   switch(p) {
      case 1: // player 1
	 if (_life1 > 0)
	    al_draw_rectangle(displayWidth - 70, 50, displayWidth - 50, 70,
			      _player1->color, 5);
	 if (_life1 > 1)
	    al_draw_rectangle(displayWidth - 110, 50, displayWidth - 90, 70,
			      _player1->color, 5);
	 if (_life1 > 2)
	    al_draw_rectangle(displayWidth - 150, 50, displayWidth - 130, 70,
			      _player1->color, 5);
	 break;
	 
      case 2: // player 2
	 if (_life2 > 0)
	    al_draw_rectangle(50, 50, 70, 70,
			      _player2->color, 5);
	 if (_life2 > 1)
	    al_draw_rectangle(90, 50, 110, 70,
			      _player2->color, 5);
	 if (_life2 > 2)
	    al_draw_rectangle(130, 50, 150, 70,
			      _player2->color, 5);
	 break;
      default:
	 break;	 
   }
}

void Versus::drawProjectiles() {
   if (!_proj.empty()) {
      for (std::vector< std::shared_ptr<Projectile> >::iterator it = _proj.begin(); 
	   it != _proj.end(); ++it) { 
	 (*it)->draw();
      }
   }
}


void Versus::drawGameOver() {
   if (!_gameOverTimer->isRunning()) {
      _gameOverTimer->startTimer();
   }
   if (_gameOverTimer->getCount() < 80) {
      _font18->drawTextCentered(al_map_rgb(255, 0, 0), "game over");
   }
   else {
      _gameOverTimer->stopTimer();
   }
}

// takes an integer equal to either 1 or 2, representing the player, and draws their score
void Versus::drawScore(int p) {
   switch(p) {
      case 1: // player1 score
	 _font18->drawTextF(al_map_rgb(255, 255, 255), 100, 200, "Score: %i", _score1);
	 break;
      case 2: // player2 score
	 _font18->drawTextF(al_map_rgb(255, 255, 255), 700, 200, "Score: %i", _score2);
	 break;
      default:
	 break;
   }
}

//===============================
// UPDATE FUNCTIONS FOR COMPONENTS
//=================================
void Versus::updateProjectiles(double dt) {
   if (!_proj.empty()) {
      for (std::vector< std::shared_ptr<Projectile> >::iterator it = _proj.begin();
	   it != _proj.end(); ++it) {
	 (*it)->update(dt);
      }
   }
}


void Versus::updateCollision() {
   // check collision on each player
   if (_player1 && _player2) { // no reason to check if either player is dead
      for (std::vector< std::shared_ptr<Projectile> >::iterator it = _proj.begin();
	   it != _proj.end(); ++it) {
	 if (!doColorsMatch((*it)->color, _player1->color)) {
	    if (pointBoxCollision((*it)->centre, _player1->centre, 16)) { // note 16 is size
	       (*it)->live = false;
	       _player1->hit(1);
	       _score2 += 1; // player2 score increase
	    }
	 }
	 if (!doColorsMatch((*it)->color, _player2->color)) {
	    if (pointBoxCollision((*it)->centre, _player2->centre, 16)) {
	       (*it)->live = false;
	       _player2->hit(1);
	       _score1 += 1; // player1 score increase
	    }
	 }
      }
   }
}


void Versus::updatePlayerStatus() {
   if (_player1 && _player1->dead) {
      _life1 -= 1;
      _player1.reset();
   }
   if (_player2 && _player2->dead) {
      _life2 -= 1;
      _player2.reset();
   }
}


//=========================
// UTILITY FUNCTIONS
//=========================
bool Versus::doColorsMatch(const ALLEGRO_COLOR& a, const ALLEGRO_COLOR& b) {
   return (a.r == b.r && a.g == b.g && a.b == b.b);
}

bool Versus::pointBoxCollision(const Point& p1, const Point& p2, 
				 const int& s2) {
   return ((p1.x > p2.x - s2) &&
	   (p1.x < p2.x + s2) &&
	   (p1.y > p2.y - s2) &&
	   (p1.y < p2.y + s2));
}
