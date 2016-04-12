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

void Boss::load_assets()
{
   
}

//draw image to display the boss ship
void Boss::draw(std::shared_ptr<Sprite> bossShip, std::shared_ptr<Sprite> bossDeath)
{
   if(!dead)
      al_draw_rectangle(centre.x, centre.y, centre.x - size, centre.y - size
		     ,al_map_rgb(155, 0, 0), 5);
      // bossShip -> draw(centre, 0);
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

   if(centre.x < 700)
      speed.x = 0;

   if(centre.y > 500 - size || centre.y < size)
      speed.reflectY();

   if(al_get_timer_count(fireDelay) > fireSpeed)
   {
      fire = true;
      al_stop_timer(fireDelay);
      al_set_timer_count(fireDelay, 0);
      al_start_timer(fireDelay);
   }
	 
}
