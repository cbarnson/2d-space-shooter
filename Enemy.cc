/**
 * @file Enemy.cc
 * @brief Implementation of Enemy class- draws, updates and destroys enemies
 *
 * @author
 * @bug
 */
#include "Enemy.h"

	
Enemy::~Enemy() {
   if(fireDelay != NULL)
      al_destroy_timer(fireDelay);
   //delete death;
}
	
void Enemy::setFire(bool f) { fire = f; }
ALLEGRO_COLOR Enemy::getColor() { return color; }
Vector Enemy::getProjSpeed() { return projSpeed; }
int Enemy::getSize() { return size; }
Point Enemy::getCentre() { return centre; }
bool Enemy::getDead() { return dead; }   
bool Enemy::getFire() { return fire; }
bool Enemy::getdAnim_complete() { return dAnim_complete; }
   
void Enemy::load_assets() {
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));

   death = make_shared<Sprite> ("explode.png");
   //death = new Sprite("explode.png");

   al_destroy_path(path);
}

void Enemy::deathAnim() {
   // dAnim specifies the column of the region to draw
   // there are 5 frames of the death anim
   // dAnim ranges from 0 to 4   
   death->draw_death_anim(dAnim, centre, 0);
   dAnim++; // move forward to the next frame of the animation for the next call
}

// decrement enemy life by a value of 1
void Enemy::hit() {
   lives = lives - 1;
   if (lives < 1)
      dead = true;
}

	
// draw image to display of enemy ship
void Enemy::draw() {
   if (!dead) {
      // draw primitive representing the enemy hitbox
      al_draw_rectangle(centre.x - size, centre.y - size,
			centre.x + size, centre.y + size,
			color, 3);
   }
   else {
      // enemy has been hit and killed, proceed through death animation sequence
      //cout << "in enemy draw pre death anim draw\n";
      if (dAnim < 5) deathAnim();
      else dAnim_complete = true;
   }      
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
