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

int BOSS_SIZE = 80;

Boss::Boss(Point cen, ALLEGRO_COLOR c, Vector spd) : Enemy(cen, c, spd),
							 projSpeed(Vector(-400, 0)),
							 fireSpeed(rand() % 40 + 30),
							 lives(30), dAnim(0),
							 dAnim_complete(false), fire(true)
{
   col=0;
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
   if(lives==20){
      col=1;
      BOSS_SIZE=70;
   }
   if(lives==10){
      BOSS_SIZE=60;
      col=2;
   }
}


//draw image to display the boss ship
void Boss::draw(std::shared_ptr<Sprite> bossShip, std::shared_ptr<Sprite> bossDeath)
{
   if(!dead)
      // al_draw_rectangle(centre.x, centre.y, centre.x - BOSS_SIZE,
      //		centre.y - BOSS_SIZE, al_map_rgb(155, 0, 0), 5);
      bossShip -> draw_boss(0, col, 200, 200, centre, 0);
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
   bossDeath -> draw_death_anim(dAnim, centre, 0);
   dAnim++;
}

// update Boss movement
void Boss::update(double dt)
{
   centre = centre + speed * dt;

   if(centre.x < 700 && speed.y == 0)
   {
      speed.x = 0;
      speed.y = 100;
   }
   
   if(centre.y > 500 - BOSS_SIZE || centre.y < BOSS_SIZE)
      speed.reflectY();

   if(fireDelay->getCount() > fireSpeed)
   {
      fire = true;
      fireDelay->stopTimer();
      fireDelay->resetCount();
      fireDelay->startTimer();
   }
	 
}
