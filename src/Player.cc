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

const int PLAYER_SIZE = 16; // in pixels
const int PLAYER_TRAVEL_SPEED = 250;
const float MAX_LIFE = 3;

Player::Player(Point p, ALLEGRO_COLOR c) : centre(p), color(c), speed(Vector(0, 0)),
					   lives(3), row(0), col(0), dead(false)
{
   
}

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
     speed.y -= PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_D)) {
     speed.x += PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_S)) {
     speed.y += PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_A)) {
     speed.x -= PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_SPACE)) {
     return act::action::FIRE_PRIMARY;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_F)) {
     return act::action::FIRE_SECONDARY;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE)) {
     return act::action::QUIT_GAME;
  }

  return act::action::NO_ACTION;
}

act::action Player::inputPlayer2(ALLEGRO_KEYBOARD_STATE& kb) {
 if (al_key_down(&kb, ALLEGRO_KEY_UP)) {
     speed.y -= PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_RIGHT)) {
     speed.x += PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_DOWN)) {
     speed.y += PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_LEFT)) {
     speed.x -= PLAYER_TRAVEL_SPEED;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_PAD_0)) {
     return act::action::FIRE_PRIMARY;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_PAD_DELETE)) {
     return act::action::FIRE_SECONDARY;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_ESCAPE)) {
     return act::action::QUIT_GAME;
  }

  return act::action::NO_ACTION;
}


void Player::draw(std::shared_ptr<Sprite> sprite, int flags) {   
   sprite->draw_region(row, col, 47.0, 40.0, centre, flags);
   drawRemainingLife();
}

void Player::update(double dt) {
   centre = centre + speed * dt;
   selectShipAnimation(); // must happen before we reset our speed
   speed = Vector(0, 0); // reset our speed
   checkBoundary();
}


void Player::selectShipAnimation() {
   if (speed.x > 0) {
      col = 1;
      if (speed.y > 0) row = 2;
      else if (speed.y < 0) row = 0;
      else row = 1;
   } else {
      col = 0;
      if (speed.y > 0) row = 2;
      else if (speed.y < 0) row = 0;
      else row = 1;
   }
}


void Player::checkBoundary() {   
   // check x bound and adjust if out
   if (centre.x > 800 - PLAYER_SIZE)
      centre.x = 800 - PLAYER_SIZE;
   else if (centre.x < PLAYER_SIZE)
      centre.x = PLAYER_SIZE;   
   // check y bound and adjust if out
   if (centre.y > 600 - PLAYER_SIZE)
      centre.y = 600 - PLAYER_SIZE;
   else if (centre.y < PLAYER_SIZE)
      centre.y = PLAYER_SIZE;
}


void Player::drawRemainingLife() {   
   al_draw_line(centre.x - PLAYER_SIZE*2, centre.y + PLAYER_SIZE*2,
		(centre.x - PLAYER_SIZE*2) + (lives / MAX_LIFE) * (PLAYER_SIZE*4),
		centre.y + PLAYER_SIZE*2,
		al_map_rgb(255 * (1.0 - lives / MAX_LIFE),
			   200 * (lives / MAX_LIFE),
			   0), 5);
}
