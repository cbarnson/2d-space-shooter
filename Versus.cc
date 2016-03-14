/**
 * @file Versus.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Versus.h"

void Versus::setup() {
   vector<int> h;
   h.push_back(ALLEGRO_KEY_UP);
   h.push_back(ALLEGRO_KEY_DOWN);
   h.push_back(ALLEGRO_KEY_RIGHT);
   h.push_back(ALLEGRO_KEY_LEFT);
   h.push_back(ALLEGRO_KEY_PAD_0);
   play.push_back(make_shared<Player> (Point(200, 300),
				       al_map_rgb(255,0,0), h,
				       false, fps ));
   h.clear();
   h.push_back(ALLEGRO_KEY_W);
   h.push_back(ALLEGRO_KEY_S);
   h.push_back(ALLEGRO_KEY_D);
   h.push_back(ALLEGRO_KEY_A);
   h.push_back(ALLEGRO_KEY_SPACE);
   play.push_back(make_shared<Player> (Point(600, 300),
				       al_map_rgb(0,200,0), h,
				       true, fps ));	 
}

bool Versus::is_game_over() {
   return game_over;
}


void Versus::update(double dt) {
   if (!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 (*it)->update(dt);
   if (!proj.empty())
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) 
	 (*it)->update(dt);          
   if (!enem.empty())
      for (list< shared_ptr<Enemy> >::iterator it = enem.begin(); it != enem.end(); ++it) {
	 (*it)->update(dt);
	 if((*it)->getFire()){
	    proj.push_back(make_shared<Projectile>((*it)->getCentre(), (*it)->getColor(),
						   (*it)->getProjSpeed()));
	    (*it)->setFire(false);
	 }	 	 
      }
}




void Versus::draw() {
   if (!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 (*it)->draw();
   if (!proj.empty())
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) 
	 (*it)->draw();
   if (!enem.empty())
      for (list< shared_ptr<Enemy> >::iterator it = enem.begin(); it != enem.end(); ++it)  
	 (*it)->draw();
}



void Versus::updatePlayer() {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->updatePlayer();	 
	 if ((*it)->getFire()) {
	    proj.push_back(make_shared<Projectile> ((*it)->getCentre(), (*it)->getColor(),
						    (*it)->getProjSpeed()));
	    (*it)->setFire(false);
	 }	 
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
	       Point A = (*i)->getCentre();
	       Point B = (*p)->getCentre(); int b = (*p)->getSize();
	       if ((A.x > B.x - b) &&
		   (A.x < B.x + b) &&
		   (A.y > B.y - b) &&
		   (A.y < B.y + b)) {
		  // is a hit on Player
		  std::cout << "hit on PLAYER\n";
		  (*i)->setDead();
		  (*p)->hit();
		  if ((*p)->getDead())
		     updateScore((*i)->getColor());
	       }       	  
	    }
	 }	 
	 // check against enemies
	 if (!enem.empty()) {
	    for (list< shared_ptr<Enemy> >::iterator e = enem.begin(); e != enem.end(); ++e) {
	       Point A = (*i)->getCentre();
	       Point B = (*e)->getCentre(); int b = (*e)->getSize();
	       if ((A.x > B.x - b) &&
		   (A.x < B.x + b) &&
		   (A.y > B.y - b) &&
		   (A.y < B.y + b)) {
		  // is a hit on Enemy
		  std::cout << "hit on ENEMY\n";
		  (*i)->setDead();
		  (*e)->hit();
		  if ((*e)->getDead())
		     updateScore((*i)->getColor());
	       }
	    }
	 }
      }
   }
}

void Versus::clean() {
   list< shared_ptr<Player> > newPlay;
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 if (!(*it)->getDead()) // if not dead
	    newPlay.push_back(*it);
      }
      play.clear();
      play.assign(newPlay.begin(), newPlay.end());      
   }

   list< shared_ptr<Projectile> > newProj;
   if (!proj.empty()) {
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) {
	 if ((*it)->getLive() && (*it)->inBound()) // if live
	    newProj.push_back(*it);
      }
      proj.clear();
      proj.assign(newProj.begin(), newProj.end());      
   }
   
   list< shared_ptr<Enemy> > newEnem;
   if (!enem.empty()) {
      for (list< shared_ptr<Enemy> >::iterator it = enem.begin(); it != enem.end(); ++it) {
	 if (!(*it)->getDead()) // if not dead
	    newEnem.push_back(*it);
      }
      enem.clear();
      enem.assign(newEnem.begin(), newEnem.end());      
   }
}

void Versus::updateScore(ALLEGRO_COLOR c) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 ALLEGRO_COLOR tmp = (*it)->getColor();
	 if (tmp.r == c.r && tmp.g == c.g && tmp.b == c.b) {
	    (*it)->setScore(1);
	    break;
	 }
      }
   }
}

void Versus::set(int code) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->set(code);
      }
   }
}


void Versus::reset(int code) {
   if (!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 (*it)->reset(code);        
}

