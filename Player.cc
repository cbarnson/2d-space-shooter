/**
 * @file Player.cc
 * @brief Implementation of Player class- handles drawing and updating of player
 *
 * @author
 * @bug
 */
#include "Player.h"

// set methods
void Player::setLives(int l) { lives = l; }
void Player::setScore(int s) { score += s; }
void Player::setFire(bool f) { fire = f; }
void Player::setmFire(bool f) { mfire = f; }

// get methods
int Player::getLives() { return lives; }
int Player::getSize() { return size; }
bool Player::getDead() { return dead; }
bool Player::getFire() { return fire; }
bool Player::getmFire() { return mfire; }
Point Player::getCentre() { return centre; }
Vector Player::getProjSpeed() { return projSpeed; }
Vector Player::getSpeed() { return speed; }
ALLEGRO_COLOR Player::getColor() { return color; }

Player::~Player() {
   if (fireDelay != NULL)
      al_destroy_timer(fireDelay);
   al_destroy_font(scoreFont);
}

void Player::hit(int damage) {
   lives = lives - damage;
   if (lives < 1)
      dead = true;
}

void Player::input(const ALLEGRO_EVENT& inputEvent) {
   switch (inputEvent.type) {      
      case ALLEGRO_EVENT_KEY_DOWN:
	 handleKeyDown(inputEvent);
	 break;	 
      case ALLEGRO_EVENT_KEY_UP:
	 handleKeyUp(inputEvent);
	 break;	 
   }
}

void Player::draw() {   
   ship->draw_region(row, col, 47.0, 40.0, centre, 0);
   drawRemainingLife();
   al_draw_textf(scoreFont, al_map_rgb(255, 255, 255), centre.x, centre.y - 60,
   		 ALLEGRO_ALIGN_CENTRE, "Score: %i", score);
}

void Player::update(double dt) {
   centre = centre + speed * dt;
   selectShipAnimation();
   speed = Vector(0, 0);
   checkBoundary();   
}


void Player::updatePlayerSpeed() {
   // up
   if (config.keys[0])
      speed.yMod(-speed_modifier);
   // down
   if (config.keys[1])
      speed.yMod(speed_modifier);
   // right
   if (config.keys[2]) 
      speed.xMod(speed_modifier);   
   // left
   if (config.keys[3])
      speed.xMod(-speed_modifier);
}


void Player::load_assets() {
   // initialize some timers
   if ((fireDelay = al_create_timer(1.0 / fps)) == NULL)
      throw std::runtime_error("Cannot create fireDelay timer");
   al_start_timer(fireDelay);
   
   if ((missileDelay = al_create_timer(1.0 / fps)) == NULL)
      throw std::runtime_error("Cannot create missileDelay timer");
   al_start_timer(missileDelay);

   

   // set some initial variable values
   projSpeed = (flipped) ? Vector(-400,0) : Vector(400,0);
   speed_modifier = 200;
   speed = Vector(0,0);
   lives = 3;
   size = 10;
   score = 0;
   row = 0;
   col = 0;      
   dead = false;
   fire = false;
   mfire = false;
   
   // get path to assets
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));

   // load in assets
   scoreFont = al_load_font("ipag.ttf", 14, 0);
   ship = make_shared<Sprite> ("Sprite.png");

   // destroy path
   al_destroy_path(path);
}

void Player::firePrimaryWeapon() {
   if (al_get_timer_count(fireDelay) > 5) {
      fire = true;
      al_stop_timer(fireDelay);
      al_set_timer_count(fireDelay, 0);
      al_start_timer(fireDelay);
   }
}

void Player::fireSecondaryWeapon() {
   if (al_get_timer_count(missileDelay) > 10) {
      mfire = true;
      al_stop_timer(missileDelay);
      al_set_timer_count(missileDelay, 0);
      al_start_timer(missileDelay);
   }	    	 
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
   switch (lives) {
      case 1:
	 al_draw_line(centre.x - size*2, centre.y + size*2,
		      centre.x - size*0.5, centre.y + size*2,
		      al_map_rgb(255, 0, 0), 4);
	 break;
      case 2:
	 al_draw_line(centre.x - size*2, centre.y + size*2,
		      centre.x + size*0.5, centre.y + size*2,
		      al_map_rgb(255, 128, 0), 4);
	 break;
      case 3:
	 al_draw_line(centre.x - size*2, centre.y + size*2,
		      centre.x + size*2, centre.y + size*2,
		      al_map_rgb(0, 255, 0), 4);
	 break;
   }
}

void Player::handleKeyDown(const ALLEGRO_EVENT& inputEvent) {
   for (unsigned int i = 0; i < config.keys.size(); i++) 
      if (inputEvent.keyboard.keycode == config.control[i])
	 config.keys[i] = true;
	 
   if (inputEvent.keyboard.keycode == ALLEGRO_KEY_SPACE) {
      firePrimaryWeapon();
   }
	 
   if (inputEvent.keyboard.keycode == ALLEGRO_KEY_M) {
      fireSecondaryWeapon();
   }	    
}

void Player::handleKeyUp(const ALLEGRO_EVENT& inputEvent) {
   for (unsigned int i = 0; i < config.keys.size(); i++) 
      if (inputEvent.keyboard.keycode == config.control[i])
	 config.keys[i] = false;	 	 
}
