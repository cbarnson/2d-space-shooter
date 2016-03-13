/**
 * @file Root.cc
 * @brief
 *
 * @author
 * @bug
 */

#include "Root.h"

/*
void Root::spawn() {
   if (enem.empty()) {
      // create 5 enemies
      for (int i = 0; i < 5; i++) {
	 //addEnem(make_shared<Enemy> (Point(
      }
   }      
   }
*/

void Root::addProj(shared_ptr<Projectile> p) {
   proj.push_back(p);
}

void Root::addEnem(shared_ptr<Enemy> e) {
   enem.push_back(e);
}

void Root::addPlay(int p) {
   vector<int> h;
   switch (p) {
      case 1: // controls for first player
	 h.push_back(ALLEGRO_KEY_UP);
	 h.push_back(ALLEGRO_KEY_DOWN);
	 h.push_back(ALLEGRO_KEY_RIGHT);
	 h.push_back(ALLEGRO_KEY_LEFT);
	 h.push_back(ALLEGRO_KEY_PAD_0);
	 play.push_back(make_shared<Player> (Point(200, 300),
					     al_map_rgb(255,0,0), h,
					     false, fps ));	 
	 break;
      case 2: // controls for second player
	 h.push_back(ALLEGRO_KEY_W);
	 h.push_back(ALLEGRO_KEY_S);
	 h.push_back(ALLEGRO_KEY_D);
	 h.push_back(ALLEGRO_KEY_A);
	 h.push_back(ALLEGRO_KEY_SPACE);
	 play.push_back(make_shared<Player> (Point(600, 300),
					     al_map_rgb(0,200,0), h,
					     true, fps ));	 
	 break;
	 // could theoretically add more players with own control scheme if desired
   }      
}



void Root::update(double dt) {
   if (!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 (*it)->update(dt);
   if (!proj.empty())
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) 
	 (*it)->update(dt);          
   if (!enem.empty())
         {
      for (list< shared_ptr<Enemy> >::iterator it = enem.begin(); it != enem.end(); ++it)
      {
	 (*it)->update(dt);
	 if((*it)->getFireE()){
	    addProj(make_shared<Projectile>((*it)->getCentreE(), (*it)->getColorE(), (*it)->getSpeedE()));
	    (*it)->setFireE(false);
	 }
      }
   }
      else{spawn();}
}



void Root::draw() {
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



void Root::updatePlayer() {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->updatePlayer();	 
	 if ((*it)->getFire()) {
	    addProj(make_shared<Projectile> ((*it)->getCentre(), (*it)->getColor(),
					     (*it)->getSpeed()));
	    (*it)->setFire(false);
	 }	 
      }
   }
}

// Player has:
// lives, which is an integer value
// Point centre, use getCentre to access

// Projectile has:
// bool live, use setDead() to set live = false
// Point centre, use getCentre to access; represented as a single (x,y) point in display

// simple square-bound box collision detection
void Root::collision() {
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

void Root::clean() {
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

void Root::updateScore(ALLEGRO_COLOR c) {
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

void Root::set(int code) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->set(code);
      }
   }
}

void Root::reset(int code) {
   if (!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 (*it)->reset(code);        
}

void Root::spawn(){
   Vector speed;
   shared_ptr<Enemy> e1, e2, e3, e4, e5;
   int n=(rand()%2)+1;
   std::cout<<n;
   int x=3;
   int count=0;
   switch(n)
   {
      case 1:
      

	 speed.x=-100;
	 speed.y=0;
	 e1=make_shared<Enemy>(Point(800, 300), al_map_rgb(204, 35, 99), speed);
	 e2=make_shared<Enemy>(Point(850, 200), al_map_rgb(204, 35, 99), speed);
	 e3=make_shared<Enemy>(Point(850, 400), al_map_rgb(204, 35, 99), speed);
	 e4=make_shared<Enemy>(Point(900, 500), al_map_rgb(204, 35, 99), speed);
	 e5=make_shared<Enemy>(Point(900, 100), al_map_rgb(204, 35, 99), speed);
	 addEnem(e1);addEnem(e2); addEnem(e3); addEnem(e4); addEnem(e5);
	 break;
      
      case 2:
      
	 speed.x=-100;
	 speed.y=-100;
	 if(static_cast<int>(al_get_time())%x==0&&count<5){
	    e1=make_shared<Enemy>(Point(800, 20), al_map_rgb(204, 35, 99), speed) ;
	    addEnem(e1);
	    count++;
	    x+=2;
	    std::cout<<"somethinghappened";
	 }
	 break;
	 
   }
}
   

