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
int BOSS_SIZE = 1;

Boss::Boss(Point cen, ALLEGRO_COLOR c, Vector spd) : Enemy(cen, c, spd),
							 projSpeed(Vector(-400, 0)),
						     fireSpeed(rand()%50+20),
							 lives(30), dAnim(0),
							 dAnim_complete(false), fire(true)
{
   col=0; row=0; 
   load_assets();
}

void Boss::load_assets()
{
   fireDelay = std::make_shared<Timer> (60);   
   fireDelay->create();
   fireDelay->startTimer();
}


Boss::~Boss()
{
   fireDelay.reset();
   //if(fireDelay != NULL)
   // al_destroy_timer(fireDelay);
}

// setter and getter methods
void Boss::setFire(bool f) { fire = f; }
ALLEGRO_COLOR Boss::getColor() { return color; }
Vector Boss::getProjSpeed() { return projSpeed; }
int Boss::getSize() { return BOSS_SIZE; }
Point Boss::getCentre() { return centre; }
bool Boss::getDead() { return dead; }   
bool Boss::getFire() { return fire; }
bool Boss::getdAnim_complete() { return dAnim_complete; }
bool Boss::getAlive() { return aliveBoss; }

//When hit, decrement lives by 1
void Boss::hit()
{
   lives -= 1;
   if(lives < 1)
   {
      dead = true;
      //aliveBoss = false;
   }
}


//draw image to display the boss ship
void Boss::draw(std::shared_ptr<Sprite> bossShip, std::shared_ptr<Sprite> bossDeath)
{
   chooseFrame();
   if(!dead)
      // al_draw_rectangle(centre.x, centre.y, centre.x - BOSS_SIZE,
      //		centre.y - BOSS_SIZE, al_map_rgb(155, 0, 0), 5);
      bossShip -> draw_boss(row, col, 200, 200, centre, 0);
   else
   {
      //Boss is dead and we proceed to the death animation
      if(dAnim < 5)
	 deathAnim(bossDeath);
      else
	  dAnim_complete = true;
   }
}

//this function is going to be a little interesting
void Boss::deathAnim(std::shared_ptr<Sprite> bossDeath)
{
   bossDeath->draw_death_anim(dAnim, centre, 0);
   dAnim++;
}

// update Boss movement
void Boss::update(double dt)
{
   centre = centre + speed * dt;

   if(centre.x < 700 && speed.y == 0)
   {
      BOSS_SIZE=80;
      speed.x = 0;
      speed.y = 100;
   }
   if(centre.y > 450 || centre.y < 150 )
      speed.reflectY();

   if(fireDelay->getCount() > fireSpeed)
   {
      fire = true;
      fireDelay->stopTimer();
      fireDelay->resetCount();
      fireDelay->startTimer();
   }
	 
}
void Boss::chooseFrame(){
   if(lives>20){
      frame=0;
   }
   if(lives<=20 && frame<3){//middle damage animation--fire speed goes up.
      fireSpeed=50;
      speed*1.5;
      BOSS_SIZE=70;
      frame++;
   }
   if(lives<=10 && frame <8){//final damage animation-- fire speed up again.
      fireSpeed=30;
      BOSS_SIZE=60;
      frame++;
   }
   row=frame/3;
   col=frame%3;
}
