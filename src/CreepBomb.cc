/**
 * @file Creep.cc
 * @brief Implementation of Enemy class- draws, updates and destroys enemies
 *
 * @author
 * @bug
 **/
#include "CreepBomb.h"

	
CreepBomb::~CreepBomb() {

}	
void CreepBomb::setFire(bool f) { fire = f; }
ALLEGRO_COLOR CreepBomb::getColor() { return color; }
Vector CreepBomb::getProjSpeed() { return projSpeed; }
int CreepBomb::getSize() { return size; }
Point CreepBomb::getCentre() { return centre; }
bool CreepBomb::getDead() { return dead; }   
bool CreepBomb::getFire() { return fire; }
bool CreepBomb::getdAnim_complete() { return dAnim_complete; }


void CreepBomb::load_assets() {

}

// decrement enemy life by a value of 1
void CreepBomb::hit() {
   lives = lives - 1;
   //change anim column
   if (lives < 1)
      dead = true;
}
	
// draw image to display of enemy ship
void CreepBomb::draw(std::shared_ptr<Sprite> enemyShip, std::shared_ptr<Sprite> enemyDeath) {
   if (!dead) {
      enemyShip->draw_tinted(centre, color, 0);
   }
   else {
      // enemy has been hit and killed, proceed through death animation sequence
      if (dAnim < 5) deathAnim(enemyDeath);
      else dAnim_complete = true;
   }      
}

void CreepBomb::deathAnim(std::shared_ptr<Sprite> enemyDeath) {
   // dAnim specifies the column of the region to draw
   // there are 5 frames of the death anim
   // dAnim ranges from 0 to 4   
   enemyDeath->draw_death_anim(dAnim, centre, 0);
   dAnim++; // move forward to the next frame of the animation for the next call
}

// update position of enemy ships
void CreepBomb::update(double dt) {
   centre = centre + speed * dt;
				
   if (centre.x < 0)
      dead = true;
   
   // check y bound and adjust if out
   if (centre.y > 600 - size || centre.y < size)
      speed.reflectY();
   
   if(fireDelay->getCount() > 5){
      //change animation row
   }
   if(fireDelay->getCount() > 10){
      //change animation row
   }
   if(fireDelay->getCount() > 15){
      //change animation row
   }
   if(fireDelay->getCount() == 100){
      fire = true;
   }
   if(fireDelay->getCount() == 120){
      fire = true;
   }
   
   if(fireDelay->getCount() > 140){
      fire = true;
      dead = true;
      fireDelay->stopTimer();
      fireDelay->resetCount();
      }
}
