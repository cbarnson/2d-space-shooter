/**
 * @file Creep.cc
 * @brief Implementation of Creep class- draws, updates and destroys enemies
 *
 * @author
 * @bug
 **/
#include "CreepMis.h"
#include <cmath>
#include "Point.h"
#include "Vector.h"
#include "Timer.h"
#include "Sprite.h"
#include<iostream>

const int CREEP_SIZE = 20;

CreepMis::CreepMis(Point cen,Point c2, Point c3, Point c4, Point c5, ALLEGRO_COLOR col, Vector spd) : Enemy(cen, col, spd),
							 projSpeed(Vector(-400, 0)),
							 fireSpeed(rand() % 50 + 30),
							 lives(1), dAnim(0),
							 dAnim_complete(false), fire(true), stop1(c2),
							 stop2(c3), stop3(c4), stop4(c5)
{
   next=stop1; at1=false; at2=false; at3=false; at4=false;
   focal.x=400; focal.y=300;
   load_assets();
}
						
// creates and starts the fireDelay timer for the Creep
void CreepMis::load_assets() {
   fireDelay = std::make_shared<Timer> (60);   
   fireDelay->create();
   fireDelay->startTimer();
}
	
CreepMis::~CreepMis() {
   fireDelay.reset();
}

// setter and getter methods
void CreepMis::setFire(bool f) { fire = f; }
ALLEGRO_COLOR CreepMis::getColor() { return color; }
Vector CreepMis::getProjSpeed() { return projSpeed; }
int CreepMis::getSize() { return CREEP_SIZE; }
Point CreepMis::getCentre() { return centre; }
bool CreepMis::getDead() { return dead; }   
bool CreepMis::getFire() { return fire; }
bool CreepMis::getdAnim_complete() { return dAnim_complete; }


// decrement enemy life by a value of 1
void CreepMis::hit() {
   lives = lives - 1;
   if (lives < 1)
      dead  =  true;
}
	
// draw image to display of enemy ship
void CreepMis::draw(std::shared_ptr<Sprite> enemyShip, std::shared_ptr<Sprite> enemyDeath) {
   if (!dead) {//should probably use draw tinted rotated
      enemyShip->draw_rotated(centre, angle, 0);
   }
   else {
      // enemy has been hit and killed, proceed through death animation sequence
      if (dAnim < 5) deathAnim(enemyDeath);
      else dAnim_complete = true;
   }      
}

void CreepMis::deathAnim(std::shared_ptr<Sprite> enemyDeath) {
   // dAnim specifies the column of the region to draw
   // there are 5 frames of the death anim
   // dAnim ranges from 0 to 4   
   enemyDeath->draw_death_anim(dAnim, centre, 0);
   dAnim++; // move forward to the next frame of the animation for the next call
}

// update position of enemy ships
void CreepMis::update(double dt) {
   updateAngle();
   centre = centre + speed * dt;
				
   if (centre.x < stop1.x && !at1){ 
      speed.Angle(stop1, centre, 3);
      at1=true;}
   if(centre.y < stop2.y&& !at2){
      speed.Angle(stop2, centre, 4);
      at2=true;}
   if(centre.x < stop3.x && !at3){
      speed.Angle(stop3, centre, 3);
      at3=true;}
   if(centre.y > stop4.y && !at4){
      speed.Angle(stop4, centre, 4);
      at4=true;
      //at1=false;
   }
   if(centre.x > stop1.x&&at1&&at2&&at3)
   {
      speed.Angle(stop1, centre, 3);
      at1=at2=at3=at4=false;
   }
      
   
   // check y bound and adjust if out
      if (centre.y > 600 - CREEP_SIZE || centre.y < CREEP_SIZE) {
      speed.reflectY();
   }

   if (fireDelay->getCount() > fireSpeed) {
      fire = true;
      fireDelay->stopTimer();
      fireDelay->resetCount();
      fireDelay->startTimer();
   }
}
void CreepMis::updateAngle()
{
   Point delta;
   if(centre.x>400)
   {
      delta.x=centre.x-400;
      delta.y=centre.y-300;
      angle=atan(delta.y/delta.x);
   }
   else
   {
      delta.x=centre.x-400;
      delta.y=centre.y-300;
      angle=atan(delta.y/delta.x)+3.14;
   }
   projSpeed.Angle(Point(400,300), centre, 0.5);
}
