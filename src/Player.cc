/**
 * @file Player.cc
 * @brief Implementation of Player class- handles drawing and updating of player
 *
 * @author
 * @bug
 */
#include "Player.h"

#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Action.h"
#include "Laser.h"
#include "Missile.h"

using namespace act;

const int PLAYER_SIZE = 16; // in pixels
const int PLAYER_TRAVEL_SPEED = 250;
const float MAX_LIFE = 3;

/*
Player::Player(Point p, ALLEGRO_COLOR c) : centre(p), color(c), 
					   speed(Vector(0, 0)), lives(3), 
					   row(0), col(0), dead(false)
{
   
}
*/

// destructor
Player::~Player() {
   
}


void Player::hit(int damage) {
   lives = lives - damage;
   if (lives < 1)
      dead = true;
}

act::action Player::input(ALLEGRO_KEYBOARD_STATE& kb) {
  if (al_key_down(&kb, ALLEGRO_KEY_W)) {
     _speed.y -= PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_D)) {
     _speed.x += PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_S)) {
     _speed.y += PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_A)) {
     _speed.x -= PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_PAD_0)||al_key_down(&kb, ALLEGRO_KEY_SPACE)) {
    return action::FIRE_PRIMARY;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_PAD_DELETE)) {
    return action::FIRE_SECONDARY;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE)) {
    return action::QUIT_GAME;
  }

  return action::NO_ACTION;
}

void Player::draw(std::shared_ptr<Sprite> sprite) {   
   sprite->draw_region(row, col, 47.0, 40.0, _centre, 0);
   drawRemainingLife();
}

void Player::update(double dt) {
   _centre = _centre + _speed * dt;
   selectShipAnimation(); // must happen before we reset our _speed
   _speed = Vector(0, 0); // reset our _speed
   checkBoundary();
}


void Player::selectShipAnimation() {
   if (_speed.x > 0) {
      col = 1;
      if (_speed.y > 0) row = 2;
      else if (_speed.y < 0) row = 0;
      else row = 1;
   } else {
      col = 0;
      if (_speed.y > 0) row = 2;
      else if (_speed.y < 0) row = 0;
      else row = 1;
   }
}


void Player::checkBoundary() {   
   // check x bound and adjust if out
   if (_centre.x > 800 - PLAYER_SIZE)
      _centre.x = 800 - PLAYER_SIZE;
   else if (_centre.x < PLAYER_SIZE)
      _centre.x = PLAYER_SIZE;   
   // check y bound and adjust if out
   if (_centre.y > 600 - PLAYER_SIZE)
      _centre.y = 600 - PLAYER_SIZE;
   else if (_centre.y < PLAYER_SIZE)
      _centre.y = PLAYER_SIZE;
}


void Player::drawRemainingLife() {   
   al_draw_line(_centre.x - PLAYER_SIZE*2, _centre.y + PLAYER_SIZE*2,
		(_centre.x - PLAYER_SIZE*2) + (lives / MAX_LIFE) * (PLAYER_SIZE*4),
		_centre.y + PLAYER_SIZE*2,
		al_map_rgb(255 * (1.0 - lives / MAX_LIFE),
			   200 * (lives / MAX_LIFE),
			   0), 5);
}
