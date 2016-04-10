/**
 * @file Boss.cc
 * @brief Implementation of Boss class
 *
 * @author
 * @bug
 **/
#include "Boss.h"

Boss::~Boss()
{
   if(fireDelay != NULL)
      al_destroy_timer(fireDelay);
}

void Boss::setFire(bool f) { fire = f; }
ALLEGRO_COLOR Boss::getColor() { return color; }
Vector Boss::getProjSpeed() { return projSpeed; }
int Boss::getSize() { return size; }
Point Boss::getCentre() { return centre; }
bool Boss::getDead() { return dead; }   
bool Boss::getFire() { return fire; }
bool Boss::getdAnim_complete() { return dAnim_complete; }

//When hit, decrement lives by 1
void Boss::hit()
{
   lives -= 1;
   if(lives <1)
      dead = true;
}

//draw image to display the boss ship
void Boss::draw(std::shared_ptr<Sprite> bossShip, std::shared_ptr<Sprite> bossDeath)
{
   if(!dead)
      bossShip -> draw(centre, 0);
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
   centre.y = centre.y + speed.y * dt;

   if(centre.x > 0)
      dead = true;

   if(centre.y > 500 - size || centre.y < 100 + size)
      speed.reflectY();

   if(al_get_timer_count(fireDelay) > fireSpeed)
   {
      fire = true;
      al_stop_timer(fireDelay);
      al_set_timer_count(fireDelay, 0);
      al_start_timer(fireDelay);
   }
	 
}
