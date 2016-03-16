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

Player::~Player() {
   if (fireDelay != NULL)
      al_destroy_timer(fireDelay);
   //al_destroy_font(scoreFont);
   //al_destroy_path(playerPath);
   delete ship;
   /*
   delete neutral_up;
   delete neutral_mid;
   delete neutral_down;
   delete forward_up;
   delete forward_mid;
   delete forward_down;*/
}

void Player::load_assets() {
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));

   ship = new Sprite("Sprite.png");
   
   //scoreFont = al_load_font("/home/barc2720/assn/alTest/resources/ipag.ttf", 48, 0);
   //neutral_up = new Sprite("/home/barc2720/assn/alTest/resources/ship00.png");   
   //neutral_mid = new Sprite("/home/barc2720/assn/alTest/resources/ship01.png");
   //neutral_down = new Sprite("/home/barc2720/assn/alTest/resources/ship10.png");
   //forward_up = new Sprite("/home/barc2720/assn/alTest/resources/ship11.png");
   //forward_mid = new Sprite("/home/barc2720/assn/alTest/resources/ship20.png");
   //forward_down = new Sprite("/home/barc2720/assn/alTest/resources/ship21.png");

   /*
   neutral_up->convert();
   neutral_mid->convert();
   neutral_down->convert();
   forward_up->convert();
   forward_mid->convert();
   forward_down->convert();
   */
   al_destroy_path(path);
}

void Player::hit() {
   lives = lives - 1;
   if (lives < 1)
      dead = true;
}

// called when ALLEGRO_EVENT_KEY_UP
void Player::set(int code) {
   for (unsigned int i = 0; i < config.keys.size(); i++) {
      if (code == config.control[i])
	 config.keys[i] = true;
   }   
}


// called when ALLEGRO_EVENT_KEY_DOWN
void Player::reset(int code) {
   for (unsigned int i = 0; i < config.keys.size(); i++) {
      if (code == config.control[i])
	 config.keys[i] = false;
   }
}   

void Player::draw() {

/*
   if (speed.x > 0) {
      if (speed.y > 0) forward_down->draw(centre, 0);
      else if (speed.y < 0) forward_up->draw(centre, 0);
      else forward_mid->draw(centre, 0);
   } else {
      if (speed.y > 0) neutral_down->draw(centre, 0);
      else if (speed.y < 0) neutral_up->draw(centre, 0);
      else neutral_mid->draw(centre, 0);
      }
*/
   // reset speed to 0
   //al_clear_to_color(al_map_rgb(0, 0, 0));

   //int row, col;
   cout << "about to draw region\n";
   ship->draw_region(row, col, centre, 0);
   //speed = Vector(0, 0);
   
   /*
   al_draw_bitmap(ship00,
		  centre.x - al_get_bitmap_width(ship00) * 0.5,
		  centre.y - al_get_bitmap_height(ship00) * 0.5, 0);
   */


/*
   
   al_draw_rectangle(centre.x - size, centre.y - size,
		     centre.x + size, centre.y + size,
		     color, 3);
*/
   cout << "region has been drawn\n";
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
   //	 ALLEGRO_ALIGN_CENTRE, "Score: %i", score);
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

    

