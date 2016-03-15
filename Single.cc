#include "Single.h"

void Single::setup() {
   vector<int> h;
   h.push_back(ALLEGRO_KEY_W);
   h.push_back(ALLEGRO_KEY_S);
   h.push_back(ALLEGRO_KEY_D);
   h.push_back(ALLEGRO_KEY_A);
   h.push_back(ALLEGRO_KEY_PAD_0);
   play.push_back(make_shared<Player> (Point(600, 300),
				       al_map_rgb(0,200,0), h,
				       false, fps ));	 
}

bool Single::is_game_over() {
   if (play.empty())
      return true;
   return false;
}


void Single::update(double dt) {
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
	    proj.push_back(make_shared<Projectile> ((*it)->getCentre(), (*it)->getColor(),
						    (*it)->getProjSpeed()));
	    (*it)->setFire(false);	    
	 }	 	 
      }
   else
      spawn();
}

void Single::draw() {
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

void Single::updatePlayer() {
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


void Single::collision() {
   if (!proj.empty()) {
      // projectiles exist
      for (list< shared_ptr<Projectile> >::iterator i = proj.begin(); i != proj.end(); ++i) {
	 // check against players
	 //if (play) {
	 
	 if (!play.empty()) {
	    for (list< shared_ptr<Player> >::iterator p = play.begin(); p != play.end(); ++p) {
	       Point A = (*i)->getCentre();
	       Point B = (*p)->getCentre(); int b = (*p)->getSize();
	       if ((A.x > B.x - b) && (A.x < B.x + b) &&
		   (A.y > B.y - b) && (A.y < B.y + b)) {
		  // is a hit on Player
		  
		  std::cout << "hit on PLAYER\n";
		  (*i)->setDead();
		  (*p)->hit(); // reduce player life
		  //if ((*p)->getDead()) // true if player is dead
		  //updateScore((*i)->getColor());
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






void Single::clean() {
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

void Single::updateScore(ALLEGRO_COLOR c) {
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

void Single::set(int code) {
   if (!play.empty()) 
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 (*it)->set(code);
}

void Single::reset(int code) {
   if (!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 (*it)->reset(code);        
}

void Single::spawn() {
   Vector speed;
   //int n = (rand() % 2) + 1;
   int n = 1;
   //std::cout<<n;
   int x = 3;
   int count = 0;
   switch(n) {
      case 1:
	 speed.x = -100;
	 speed.y = 0;
	 enem.push_back(make_shared<Enemy>(Point(800, 300), al_map_rgb(204, 35, 99), speed));
	 enem.push_back(make_shared<Enemy>(Point(850, 200), al_map_rgb(204, 35, 99), speed));
	 enem.push_back(make_shared<Enemy>(Point(850, 400), al_map_rgb(204, 35, 99), speed));
	 enem.push_back(make_shared<Enemy>(Point(900, 500), al_map_rgb(204, 35, 99), speed));
	 enem.push_back(make_shared<Enemy>(Point(900, 100), al_map_rgb(204, 35, 99), speed));
	 break;
      
      case 2:      
	 speed.x = -100;
	 speed.y = -100;
	 if (static_cast<int> (al_get_time()) % x == 0 && count < 5) {
	    enem.push_back(make_shared<Enemy> (Point(800, 20), al_map_rgb(204, 35, 99), speed));
	    count++;
	    x += 2;
	    //std::cout << "somethinghappened";
	 }
	 break;	 
   }   
}
