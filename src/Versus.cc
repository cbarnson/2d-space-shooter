/**
 * @file Versus.cc
 * @brief Implementation of Versus class- handles game interactions for versus 
 *        mode
 *
 * @author
 * @bug
 */

#include "Versus.h"
#include "Missile.h"
#include "Laser.h"

Versus::~Versus() {
   proj.clear();
   play.clear();
}

void Versus::setup() {
   vector<int> h;
   h.push_back(ALLEGRO_KEY_UP);
   h.push_back(ALLEGRO_KEY_DOWN);
   h.push_back(ALLEGRO_KEY_RIGHT);
   h.push_back(ALLEGRO_KEY_LEFT);
   play.push_back(make_shared<Player> (Point(200, 300),
				       al_map_rgb(255,0,0), h,
				       framesPerSec ));
   h.clear();
   h.push_back(ALLEGRO_KEY_W);
   h.push_back(ALLEGRO_KEY_S);
   h.push_back(ALLEGRO_KEY_D);
   h.push_back(ALLEGRO_KEY_A);
   play.push_back(make_shared<Player> (Point(600, 300),
				       al_map_rgb(0,200,0), h,
				       framesPerSec ));	 
}

// if less than 2 players are in the game return true (game is over)
bool Versus::is_game_over() {
   if (2 > play.size())
      return true;
   return false;
}

// MAIN UPDATE FUNCTION
void Versus::update(double dt) {
   updatePlayerAction();
   updatePlayerPosition(dt);
   updateProjectilePosition(dt);
   collision();
   clean();
}

// MAIN DRAW FUNCTION
void Versus::draw() {
   al_clear_to_color(al_map_rgb(50, 0, 0));
   if (!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 (*it)->draw();
   if (!proj.empty())
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) 
	 (*it)->draw();
   al_flip_display();
}

void Versus::updatePlayerAction() {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->updatePlayerSpeed();	 
	 if ((*it)->fire) {
	    proj.push_back(make_shared<Laser> ((*it)->centre, (*it)->color,
					       (*it)->projSpeed));
	    (*it)->fire = false;
	 }
	 if ((*it)->mfire) {
	    proj.push_back(make_shared<Missile> ((*it)->centre, (*it)->color,
						 (*it)->projSpeed));
	    (*it)->mfire = false;	 	 
	 }	 
      }
   }   
}

void Versus::updatePlayerPosition(double dt) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->update(dt);
      }
   }   
}

void Versus::updateProjectilePosition(double dt) {
   if (!proj.empty()) {
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) {
	 (*it)->update(dt);
      }
   }
}

// simple square-bound box collision detection
void Versus::collision() {
   if (!proj.empty()) {
      // projectiles exist
      for (list< shared_ptr<Projectile> >::iterator i = proj.begin(); i != proj.end(); ++i) {
	 // check against players
	 if (!play.empty()) {
	    for (list< shared_ptr<Player> >::iterator p = play.begin(); p != play.end(); ++p) {
	       Point A = (*i)->centre;
	       Point B = (*p)->centre; int b = (*p)->size;
	       if ((A.x > B.x - b) &&
		   (A.x < B.x + b) &&
		   (A.y > B.y - b) &&
		   (A.y < B.y + b)) {
		  // is a hit on Player
		  std::cout << "hit on PLAYER\n";
		  (*i)->live = false;
		  (*p)->hit(1);
		  if ((*p)->dead)
		     updateScore((*i)->color);
	       }       	  
	    }
	 }
      }
   }
}

void Versus::clean() {
   cullPlayers();
   cullProjectiles();
}


void Versus::cullPlayers() {
   list< shared_ptr<Player> > newPlay;
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 if (!(*it)->dead) // if not dead
	    newPlay.push_back(*it);
      }
      play.clear();
      play.assign(newPlay.begin(), newPlay.end());      
   }
}

void Versus::cullProjectiles() {
   list< shared_ptr<Projectile> > newProj;
   if (!proj.empty()) {
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) {
	 if ((*it)->live) // if live
	    newProj.push_back(*it);
      }
      proj.clear();
      proj.assign(newProj.begin(), newProj.end());      
   }
}

void Versus::updateScore(const ALLEGRO_COLOR& c) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 ALLEGRO_COLOR tmp = (*it)->color;
	 if (tmp.r == c.r && tmp.g == c.g && tmp.b == c.b) {
	    (*it)->score += 1;
	    break;
	 }
      }
   }
}

void Versus::input(const ALLEGRO_EVENT& inputEvent) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it_play = play.begin(); it_play != play.end();
	   ++it_play) {
	 (*it_play)->input(inputEvent);
      }
   }
}
