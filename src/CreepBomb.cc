/**
 * @file Creep.cc
 * @brief Implementation of Enemy class- draws, updates and destroys enemies
 *
 * @author
 * @bug
 **/
#include "CreepBomb.h"
#include "Timer.h"


CreepBomb::CreepBomb(Point cen, ALLEGRO_COLOR col, Vector spd) : Enemy(cen, col, spd) {
   projSpeed = Vector(-500, 0);//not used
   lives = 3;
   size = 20;   
   dAnim = 0;      
   dAnim_complete = false;
   fire = false;
   
   load_assets();
}
	
CreepBomb::~CreepBomb() {

}

// setter and getter methods
void CreepBomb::setFire(bool f) { fire = f; }
ALLEGRO_COLOR CreepBomb::getColor() { return color; }
Vector CreepBomb::getProjSpeed() { return speed; }//not used
int CreepBomb::getSize() { return size; }
Point CreepBomb::getCentre() { return centre; }
bool CreepBomb::getDead() { return dead; }   
bool CreepBomb::getFire() { return fire; }
bool CreepBomb::getdAnim_complete() { return dAnim_complete; }


void CreepBomb::load_assets() {
   row =0; col=0;
   std::cout << "in creepbomb load assets\n";
   
   fireDelay = std::make_shared<Timer> (60);
   fireDelay->create();
   fireDelay->startTimer();
   
   projSpeed = Vector(-500, 0);//not used
   lives = 3;
   size = 20;   
   dAnim = 0;      
   dAnim_complete = false;
   fire = false; fired=false; fire2=false;
}

// decrement enemy life by a value of 1
void CreepBomb::hit() {
   lives = lives - 1;
   col++;
   //change anim column
   if (lives < 1)
      dead = true;
}
	
// draw image to display of enemy ship
void CreepBomb::draw(std::shared_ptr<Sprite> enemyShip, std::shared_ptr<Sprite> enemyDeath) {
   if (!dead) {
      enemyShip->draw_region(row, col, 40, 41, centre, 0);
   }
   else {
      // enemy has been hit and killed, proceed through death animation sequence
      if (dAnim < 5) deathAnim(enemyDeath);
      else{ dAnim_complete = true;}
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
   
   if(centre.x<670&&row==0){
      row++;  
   }
   if(centre.x<540&& row==1){
      row++;
   }
   if(centre.x<400 && !fired){
      std::cout<<"firing";
      fire = true;
      fired = true;
      dead = true;
      fireDelay->stopTimer();
      fireDelay->resetCount();
   }
}
