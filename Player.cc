/**
 * @file Player.cc
 */

#include "Player.h"

// set methods
void Player::setLives(int l) { lives = l; }
void Player::setScore(int s) { score += s; }
void Player::setFire(bool f) { fire = f; }
//void Player::setDead() { dead = true; }
void Player::hit() {
   lives = lives - 1;
   if (lives < 1)
      dead = true;
}

// get methods
int Player::getLives() { return lives; }
int Player::getSize() { return size; }
bool Player::getDead() { return dead; }
bool Player::getFire() { return fire; }
Point Player::getCentre() { return centre; }
Vector Player::getSpeed() { return projSpeed; }
ALLEGRO_COLOR Player::getColor() { return color; }


// called when ALLEGRO_EVENT_KEY_UP
void Player::set(int code) {
   for (int i = 0; i < 5; i++) {
      if (code == config.control[i])
	 config.keys[i] = true;
   }   
}


// called when ALLEGRO_EVENT_KEY_DOWN
void Player::reset(int code) {
   for (int i = 0; i < 5; i++) {
      if (code == config.control[i])
	 config.keys[i] = false;
   }
}   

void Player::draw() {
   al_draw_rectangle(centre.x - size, centre.y - size,
		     centre.x + size, centre.y + size,
		     color, 3);
   switch (lives) {
      case 1:
	 al_draw_line(centre.x - size*2, centre.y + size*2,
		      centre.x - size*0.5, centre.y + size*2,
		      al_map_rgb(255, 0, 0), 4);
	 break;
      case 2:
	 al_draw_line(centre.x - size*2, centre.y + size*2,
		      centre.x + size*0.5, centre.y + size*2,
		      al_map_rgb(255, 128, 0), 4);
	 break;
      case 3:
	 al_draw_line(centre.x - size*2, centre.y + size*2,
		      centre.x + size*2, centre.y + size*2,
		      al_map_rgb(0, 255, 0), 4);
	 break;
   }
   
   //al_draw_bitmap(ship, current.x, current.y, 0);
   
   al_draw_textf(scoreFont, color, centre.x, centre.y - 60, ALLEGRO_ALIGN_CENTRE,
		 "Score: %i", score);
}

void Player::updatePlayer() {
   // up
   if (config.keys[0]) 
      speed.yMod(-speed_modifier);
   // down
   if (config.keys[1])
      speed.yMod(speed_modifier);
   // right
   if (config.keys[2]) 
      speed.xMod(speed_modifier);      
   // left
   if (config.keys[3]) 
      speed.xMod(-speed_modifier);

   // fire
   if (config.keys[4] && (al_get_timer_count(fireDelay) > 5)) {
      fire = true;
      al_stop_timer(fireDelay);
      al_set_timer_count(fireDelay, 0);
      al_start_timer(fireDelay);
   }
}

void Player::update(double dt) {
   centre = centre + speed * dt;
   speed = Vector(0, 0);
      
   // check x bound and adjust if out
   if (centre.x > 800 - size)
      centre.x = 800 - size;
   else if (centre.x < size)
      centre.x = size;
   
   // check y bound and adjust if out
   if (centre.y > 600 - size)
      centre.y = 600 - size;
   else if (centre.y < size)
      centre.y = size;
      
}
/*      
   // COLLISION PLAYER 1 SHOTS, CHECKING FOR HITS ON PLAYER 2
   if (!otherPlayers.empty() && !curProjectiles.empty())  {
      for (list< shared_ptr<Player> >::iterator i = otherPlayers.begin();
	   i != otherPlayers.end(); ++i) {
	       
	 if ((*i)->getLive()) {
		  
	    for (list< shared_ptr<Projectile> >::iterator j = curProjectiles.begin();
		 j != curProjectiles.end(); ++j) {
		     
	       if ((*j)->getLive()) {
		  Point temp = (*i)->getCurrent();
		  Point boundTopLeft = Point(temp.x, temp.y - (size * 0.5));
		  Point boundBotRight = Point(temp.x + size, temp.y + (size * 0.5));
		  Point shot = (*j)->getCenter();
			
		  if ((shot.x > boundTopLeft.x) &&
		      (shot.x < boundBotRight.x) &&
		      (shot.y > boundTopLeft.y) &&
		      (shot.y < boundBotRight.y)) {
		     // hit
		     (*i)->setLive(false);
		     (*j)->setLive(false);
		     std::cout << "HIT ON ----PLAYER2-----" << std::endl;
		     break; // continue to the next player or exit the loop if no more
		  }
	       }
	    }
	 }
      }
   }

   // COLLISION PLAYER 2 SHOTS, CHECKING FOR HITS ON PLAYER 1
   if (!otherPlayers.empty()) {

      for (list< shared_ptr<Player> >::iterator p = otherPlayers.begin();
	   p != otherPlayers.end(); ++p) {
	    
	 if ((*p)->getLive() && !(*p)->curProjectiles.empty()) {

	    list< shared_ptr<Projectile> > proj((*p)->curProjectiles);
	    for (list< shared_ptr<Projectile> >::iterator i = proj.begin();
		 i != proj.end(); ++i) {
		  
	       if ((*i)->getLive()) {
		     
		  Point boundTopLeft = Point(current.x - size, current.y - (size * 0.5));
		  Point boundBotRight = Point(current.x, current.y + (size * 0.5));
		  Point shot = (*i)->getCenter();
		     
		  if ((shot.x > boundTopLeft.x) &&
		      (shot.x < boundBotRight.x) &&
		      (shot.y > boundTopLeft.y) &&
		      (shot.y < boundBotRight.y)) {
		     // hit
		     (*i)->setLive(false);
		     setLive(false);
		     std::cout << "HIT ON ----PLAYER1-----" << std::endl;
		     break; // continue to the next player or exit the loop if no more
		  }
	       }		  
	    }
	 }
      }	       
   }
*/

/*   
   // CLEAR PLAYERS AND PROJECTILES FOR WHICH LIVE = FALSE
   list< shared_ptr<Projectile> > newList;	 
   for (list< shared_ptr<Projectile> >::iterator it = curProjectiles.begin();
	it != curProjectiles.end(); ++it) {
      if ((*it)->getLive()) 
	 newList.push_back(*it); 	    	    
   }
   curProjectiles.clear();	 
   curProjectiles.assign(newList.begin(), newList.end());       


      
   list< shared_ptr<Player> > newListPlayer;	       
   for (list< shared_ptr<Player> >::iterator it = otherPlayers.begin();
	it != otherPlayers.end(); ++it) {
	 
      if ((*it)->getLive()) {
	 newListPlayer.push_back(*it);

	 if (!(*it)->curProjectiles.empty()) {

	    list< shared_ptr<Projectile> > listPlayerProj((*it)->curProjectiles);
	    list< shared_ptr<Projectile> > newListPlayerProj;
	    for (list< shared_ptr<Projectile> >::iterator j = listPlayerProj.begin();
		 j != listPlayerProj.end(); ++j) {
		  
	       if ((*j)->getLive()) {
		  newListPlayerProj.push_back(*j);
	       }
	    }
	    (*it)->curProjectiles.clear();
	    (*it)->curProjectiles.assign(newListPlayerProj.begin(),
					 newListPlayerProj.end());
	 }
      }
   }
   otherPlayers.clear();	 
   otherPlayers.assign(newListPlayer.begin(), newListPlayer.end());
      
*/
      
    

