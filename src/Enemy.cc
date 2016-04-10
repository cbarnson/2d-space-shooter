/**
 * @file Enemy.cc
 * @brief Implementation of Enemy class- draws, updates and destroys enemies
 *
 * @author
 * @bug
 */
#include "Enemy.h"
#include "Sprite.h"
#include <iostream>
#include <stdexcept>


Enemy::Enemy(Point p, ALLEGRO_COLOR c, Vector s) : centre(p), color(c), speed(s) {
   if((fireDelay = al_create_timer(1.0 / 60)) == NULL) //NOTE MUST BE CHANGED LATER
      throw std::runtime_error("cannot create fireDelay timer");
   al_start_timer(fireDelay);
      
   projSpeed = Vector(-500, 0);
   fireSpeed = (rand() % 20) + 80;  
   lives = 1;
   size = 20;
      
   dAnim = 0;      
   dAnim_complete = false;
   dead = false;
   fire = true;
}


Enemy::~Enemy() {
   if(fireDelay != NULL)
      al_destroy_timer(fireDelay);   
}
	
void Enemy::setFire(bool f) { fire = f; }
ALLEGRO_COLOR Enemy::getColor() { return color; }
Vector Enemy::getProjSpeed() { return projSpeed; }
int Enemy::getSize() { return size; }
Point Enemy::getCentre() { return centre; }
bool Enemy::getDead() { return dead; }   
bool Enemy::getFire() { return fire; }
bool Enemy::getdAnim_complete() { return dAnim_complete; }


// decrement enemy life by a value of 1
void Enemy::hit() {
   lives = lives - 1;
   if (lives < 1)
      dead = true;
}

	
// draw image to display of enemy ship
void Enemy::draw(std::shared_ptr<Sprite> enemyShip, std::shared_ptr<Sprite> enemyDeath) {
   if (!dead) {
      enemyShip->draw_tinted(centre, color, 0);
   }
   else {
      // enemy has been hit and killed, proceed through death animation sequence
      if (dAnim < 5) deathAnim(enemyDeath);
      else dAnim_complete = true;
   }      
}

void Enemy::deathAnim(std::shared_ptr<Sprite> enemyDeath) {
   // dAnim specifies the column of the region to draw
   // there are 5 frames of the death anim
   // dAnim ranges from 0 to 4   
   enemyDeath->draw_death_anim(dAnim, centre, 0);
   dAnim++; // move forward to the next frame of the animation for the next call
}

// update position of enemy ships
void Enemy::update(double dt) {
   centre = centre + speed * dt;
				
   if (centre.x < 0)
      dead = true;
   
   // check y bound and adjust if out
   if (centre.y > 600 - size || centre.y < size)
      speed.reflectY();
		
   if(al_get_timer_count(fireDelay) > fireSpeed){
      fire = true;
      al_stop_timer(fireDelay);
      al_set_timer_count(fireDelay, 0);
      al_start_timer(fireDelay);
   }    
}
