/**
 * @file Player.cc
 * @brief Implementation of Player class- handles drawing and updating of player
 *
 * @author
 * @bug
 */
#include "Player.h"
#include <iostream>

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
   al_destroy_font(scoreFont);
   //delete ship;
}

void Player::load_assets() {
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));

   scoreFont = al_load_font("ipag.ttf", 14, 0);
   //ship = new Sprite("Sprite.png");
   cout << "player loading sprite\n";
   ship = make_shared<Sprite> ("Sprite.png");
   cout << "player loaded sprite\n";
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
<<<<<<< HEAD
<<<<<<< HEAD
   // al_draw_rectangle(centre.x - size, centre.y - size,
//		     centre.x + size, centre.y + size,
//		     color, 3);
  
   //sprite changed points from current
   //changing from centre.x-size
   //frameHeight and Width work as is!! dont think about it
   int fx = (animCol*frameWidth); //animCols
   int fy = (animRow*frameHeight); 
   
   al_draw_bitmap_region(ship, fx, fy, frameWidth, frameHeight,
			 (centre.x - (frameWidth/2)),
			 (centre.y - (frameHeight/2)), 0);

   //al_draw_bitmap(ship, centre.x-frameWidth, centre.y - frameHeight, 0);
   al_draw_textf(scoreFont, color, centre.x, centre.y - 60,
		 ALLEGRO_ALIGN_CENTRE,
		 "Score: %i", score);
=======

   //cout << "about to draw region\n";
=======
   
   cout << "player about to draw region\n";
>>>>>>> 2player
   ship->draw_region(row, col, 47.0, 40.0, centre, 0);
   cout << "player region has been drawn\n";
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
   
   al_draw_textf(scoreFont, al_map_rgb(255, 255, 255), centre.x, centre.y - 60,
   		 ALLEGRO_ALIGN_CENTRE, "Score: %i", score);
>>>>>>> bce9dd668c6fa32b872f3c8ae3f237ff53541e1a
}

void Player::updatePlayer() {
   // up
   if (config.keys[0])
   {
      //animRow = 0;
      speed.yMod(-speed_modifier);
   }
   // down
   if (config.keys[1])
   {
      //animRow = 2;
      speed.yMod(speed_modifier);
   }

   // right
   if (config.keys[2])
   {
      //animCol = 1;
      speed.xMod(speed_modifier);
   }
   // left
   if (config.keys[3])
   {
      //animCol = 2;
      speed.xMod(-speed_modifier);
<<<<<<< HEAD
   }
=======
>>>>>>> bce9dd668c6fa32b872f3c8ae3f237ff53541e1a
   // fire
   if (config.keys[4] && (al_get_timer_count(fireDelay) > 5)) {
      fire = true;
      al_stop_timer(fireDelay);
      al_set_timer_count(fireDelay, 0);
      al_start_timer(fireDelay);
   }   
}

/********void Player::resetAnimation()
{
   if()
   {
      animRow = 1;
   }
   else
      currFrame = 0;
      }*/
void Player::update(double dt) {
<<<<<<< HEAD
   centre = centre + speed * dt;
   
   //for changing the frame of animation! 
   if(speed.x > 0)
      animCol = 1;
   else if(speed.x < 0)
      animCol = 2;
   else
      animCol = 0;
   
   if(speed.y > 0)
      animRow = 2;
   else if(speed.y < 0)
      animRow = 0;
   else
      animRow = 1;

=======
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
   
>>>>>>> bce9dd668c6fa32b872f3c8ae3f237ff53541e1a
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

    

