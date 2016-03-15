/**
 * @file Player.cc
 */

#include "Player.h"

// set methods
void Player::setLives(int l) { lives = l; }
void Player::setScore(int s) { score += s; }
void Player::setFire(bool f) { fire = f; }

// get methods
int Player::getLives() { return lives; }
int Player::getSize() { return size; }
bool Player::getDead() { return dead; }
bool Player::getFire() { return fire; }
Point Player::getCentre() { return centre; }
Vector Player::getProjSpeed() { return projSpeed; }
Vector Player::getSpeed() { return speed; }
ALLEGRO_COLOR Player::getColor() { return color; }

void Player::hit() {
   lives = lives - 1;
   if (lives < 1)
      dead = true;
}

// called when ALLEGRO_EVENT_KEY_UP
void Player::set(int code) {
   for (int i = 0; i < config.keys.size(); i++) {
      if (code == config.control[i])
	 config.keys[i] = true;
   }   
}


// called when ALLEGRO_EVENT_KEY_DOWN
void Player::reset(int code) {
   for (int i = 0; i < config.keys.size(); i++) {
      if (code == config.control[i])
	 config.keys[i] = false;
   }
}   

void Player::draw() {
   /*
   if (speed.x > 0) {
      if (speed.y > 0)
	 al_draw_bitmap(ship01,
			centre.x - (al_get_bitmap_width(ship01) * 0.5),
			centre.y - (al_get_bitmap_height(ship01)* 0.5), 0);
      else if (speed.y < 0)
	 al_draw_bitmap(ship21,
			centre.x - (al_get_bitmap_width(ship21) * 0.5),
			centre.y - (al_get_bitmap_height(ship21)* 0.5), 0);
      else
	 al_draw_bitmap(ship11,
			centre.x - (al_get_bitmap_width(ship11) * 0.5),
			centre.y - (al_get_bitmap_height(ship11)* 0.5), 0);
   } else {
      if (speed.y > 0)
	 al_draw_bitmap(ship00,
			centre.x - (al_get_bitmap_width(ship00) * 0.5),
			centre.y - (al_get_bitmap_height(ship00)* 0.5), 0);
      else if (speed.y < 0)
	 al_draw_bitmap(ship20,
			centre.x - (al_get_bitmap_width(ship20) * 0.5),
			centre.y - (al_get_bitmap_height(ship20)* 0.5), 0);
      else
	 al_draw_bitmap(ship10,
			centre.x - (al_get_bitmap_width(ship10) * 0.5),
			centre.y - (al_get_bitmap_height(ship10)* 0.5), 0);
   }
   */


   al_draw_rectangle(centre.x - size, centre.y - size,
		     centre.x + size, centre.y + size,
		     color, 3);

   
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
   
   //al_draw_textf(scoreFont, al_map_rgb(255, 255, 255), centre.x, centre.y - 60,
   // ALLEGRO_ALIGN_CENTRE, "Score: %i", score);
}

void Player::updatePlayer() {
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
   // fire
   if (config.keys[4] && (al_get_timer_count(fireDelay) > 5)) {
      fire = true;
      al_stop_timer(fireDelay);
      al_set_timer_count(fireDelay, 0);
      al_start_timer(fireDelay);
   }
}

void Player::update(double dt) {
   centre = centre + speed * dt;
   speed = Vector(0, 0);
   
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

    

