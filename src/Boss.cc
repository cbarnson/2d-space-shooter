/**
 * @file Boss.cc
 * @brief Implementation of Boss class
 *
 * @author
 * @bug
 **/
#include "Boss.h"

#include "Point.h"
#include "Vector.h"
#include "Timer.h"
#include "Sprite.h"
#include <iostream>

//boss size is 60-80 depending on damage level-- set to one off the start so the boss is
// "invulnerable" while entering the screen.
const int BOSS_HP = 30;

Boss::Boss(Point cen, ALLEGRO_COLOR c, Vector spd) : Enemy(cen, c, spd),
						     projSpeed(Vector(-400, 0)),
						     fireSpeed(40),
						     lives(30), dAnim(0),
						     dAnim_complete(false), fire(true)
{
   hitbox = 1;
   targetable = false;
   col = 0;
   row = 0; 
   load_assets();
}

void Boss::load_assets() {
   fireDelay = std::make_shared<Timer> (60);   
   fireDelay->create();
   fireDelay->startTimer();
}


Boss::~Boss() {
   fireDelay.reset();
}

// get methods
ALLEGRO_COLOR Boss::getColor() { return color; }
Vector Boss::getProjSpeed() { return projSpeed; }
int Boss::getSize() { return hitbox; }
Point Boss::getCentre() { return centre; }
bool Boss::getDead() { return dead; }   
bool Boss::getFire() { return fire; }
bool Boss::getdAnim_complete() { return dAnim_complete; }
bool Boss::getAlive() { return aliveBoss; }

// set methods
void Boss::setFire(bool f) { fire = f; }

//When hit, decrement lives by 1
void Boss::hit() {
   lives -= 1;
   if(lives < 1) {
      dead = true;
   }
}


//draw image to display the boss ship
void Boss::draw(std::shared_ptr<Sprite> bossShip, std::shared_ptr<Sprite> bossDeath) {
   chooseFrame();
   if (!dead) {
      bossShip -> draw_boss(row, col, 200, 200, centre, 0);
   }
   else {
      //Boss is dead and we proceed to the death animation
      if (dAnim < 5) 
	 deathAnim(bossDeath);
      else
	 dAnim_complete = true;
   }
}

//this function is going to be a little interesting
void Boss::deathAnim(std::shared_ptr<Sprite> bossDeath) {
   bossDeath->draw_death_anim(dAnim, centre, 0);
   dAnim++;
}

// update Boss movement
void Boss::update(double dt) {
   // update position
   centre = centre + speed * dt;
   
   if(centre.x < 700 && !targetable) {
      targetable = true;// becomes targetable
      hitbox = 80;      // set hitbox to 80
      speed.x = 0;      // no more x movement      
      speed.y = 100;    // begin downward movement
   }
   // reflect conditions
   if (centre.y > 450 && speed.y > 0) { // if below mark and moving downwards
      speed.reflectY();
   }
   if (centre.y < 150 && speed.y < 0) { // if above mark and moving upwards
      speed.reflectY();
   }
   // check fire condition
   if (fireDelay->getCount() > fireSpeed) {
      fire = true;
      fireDelay->srsTimer(); // stop, reset, start
   }	 
}

// for animation
void Boss::chooseFrame() {
   if (lives > BOSS_HP){
      spriteSheetIndex = 0;
   }
   // middle damage animation--fire speed goes up.
   if (lives <= BOSS_HP && spriteSheetIndex < 3) { 
      fireSpeed = 50;
      speed = speed * 1.5; // increase speed
      hitbox = 70;
      spriteSheetIndex++;
   }
   // final damage animation-- fire speed up again
   if (lives <= 10 && spriteSheetIndex < 8) {
      fireSpeed = 30;
      speed = speed * 1.2; // increase speed
      hitbox = 60;
      spriteSheetIndex++;
   }
   // interpret index as row and col of sprite sheet
   row = spriteSheetIndex / 3;
   col = spriteSheetIndex % 3;
}
