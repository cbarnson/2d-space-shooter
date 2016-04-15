/**
 * @file Creep.cc
 * @brief Implementation of Creep class- draws, updates and destroys enemies
 *
 * @author
 * @bug
 **/
#include "Creep.h"

#include "Point.h"
#include "Vector.h"
#include "Timer.h"
#include "Sprite.h"

const int CREEP_SIZE = 20;

Creep::Creep(Point cen, ALLEGRO_COLOR col, Vector spd) : Enemy(cen, col, spd),
							 projSpeed(Vector(-400, 0)),
							 fireSpeed(rand() % 50 + 30),
							 lives(1), dAnim(0),
							 dAnim_complete(false), fire(true)
{
   load_assets();
}
						
// creates and starts the fireDelay timer for the Creep
void Creep::load_assets() {
   fireDelay = std::make_shared<Timer> (60);   
   fireDelay->create();
   fireDelay->startTimer();
}
	
Creep::~Creep() {
   fireDelay.reset();
}

// setter and getter methods
void Creep::setFire(bool f) { fire = f; }
ALLEGRO_COLOR Creep::getColor() { return color; }
Vector Creep::getProjSpeed() { return projSpeed; }
int Creep::getSize() { return CREEP_SIZE; }
Point Creep::getCentre() { return centre; }
bool Creep::getDead() { return dead; }   
bool Creep::getFire() { return fire; }
bool Creep::getdAnim_complete() { return dAnim_complete; }


// decrement enemy life by a value of 1
void Creep::hit() {
   lives = lives - 1;
   if (lives < 1)
      dead = true;
}
	
// draw image to display of enemy ship
void Creep::draw(std::shared_ptr<Sprite> enemyShip, std::shared_ptr<Sprite> enemyDeath) {
   if (!dead) {
      enemyShip->draw_tinted(centre, color, 0);
   }
   else {
      // enemy has been hit and killed, proceed through death animation sequence
      if (dAnim < 5) deathAnim(enemyDeath);
      else dAnim_complete = true;
   }      
}

void Creep::deathAnim(std::shared_ptr<Sprite> enemyDeath) {
   // dAnim specifies the column of the region to draw
   // there are 5 frames of the death anim
   // dAnim ranges from 0 to 4   
   enemyDeath->draw_death_anim(dAnim, centre, 0);
   dAnim++; // move forward to the next frame of the animation for the next call
}

// update position of enemy ships
void Creep::update(double dt) {
   centre = centre + speed * dt;
				
   if (centre.x < 0) {
      dead = true;
      return;
   }
   
   // check y bound and adjust if out
   if (centre.y > 600 - CREEP_SIZE &&speed.y > 0)  
      speed.reflectY();
   if (centre.y < 0 - CREEP_SIZE && speed.y < 0)
      speed.reflectY();


   if (fireDelay->getCount() > fireSpeed) {
      fire = true;
      fireDelay->stopTimer();
      fireDelay->resetCount();
      fireDelay->startTimer();
   }
}
