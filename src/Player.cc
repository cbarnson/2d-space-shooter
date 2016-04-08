/**
 * @file Player.cc
 * @brief Implementation of Player class- handles drawing and updating of player
 *
 * @author
 * @bug
 */

#include "Point.h"
#include "Vector.h"
#include "Sprite.h"
#include "Player.h"
#include "Action.h"
using namespace act;

const float MAX_LIFE = 3;

Player::Player(Point p, ALLEGRO_COLOR c) :
  centre(p), color(c)
{ 
   // set some initial variable values
   projSpeed = Vector(500, 0);
   speed_modifier = 250;
   speed = Vector(0, 0);
   lives = 3;
   size = 16;
   row = 0;
   col = 0;      
   dead = false;
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
    speed.y -= speed_modifier;    
  }
  if (al_key_down(&kb, ALLEGRO_KEY_D)) {
    speed.x += speed_modifier;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_S)) {
    speed.y += speed_modifier;
  }
  if (al_key_down(&kb, ALLEGRO_KEY_A)) {
    speed.x -= speed_modifier;
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
   sprite->draw_region(row, col, 47.0, 40.0, centre, 0);
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
   if (centre.x > 800 - size)
      centre.x = 800 - size;
   else if (centre.x < size)
      centre.x = size;   
   // check y bound and adjust if out
   if (centre.y > 600 - size)
      centre.y = 600 - size;
   else if (centre.y < size)
      centre.y = size;
}


void Player::drawRemainingLife() {   
   al_draw_line(centre.x - size*2, centre.y + size*2,
		(centre.x - size*2) + (lives / MAX_LIFE) * (size*4),
		centre.y + size*2,
		al_map_rgb(255 * (1.0 - lives / MAX_LIFE),
			   200 * (lives / MAX_LIFE),
			   0), 5);
}
