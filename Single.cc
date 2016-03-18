#include "Single.h"

Single::~Single() {
   //delete map1;
   proj.clear();
   enem.clear();
   play.clear();
   cout << "destructor\n";
}

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

void Single::load_assets() {
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   //cout << "about to load map\n";
   //map1 = new Sprite("green-space.png");
   //cout << "map has been loaded\n";
   
   al_destroy_path(path);   
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
   //cout << "inside single draw beginning\n";
   al_clear_to_color(al_map_rgb(0, 0, 0));
   //map1->set_as_display();
   //map1->drawToOrigin();
   
   //cout << "after clear to color\n";
   if (!play.empty()) {
      //cout << "inside if .empty()\n";
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->draw();
      }
   }
   //cout << "after player\n";
   if (!proj.empty()) {
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it){ 
	 (*it)->draw();
      }
   }
   //cout << "after proj\n";
   if (!enem.empty()) {
      for (list< shared_ptr<Enemy> >::iterator it = enem.begin(); it != enem.end(); ++it) {
	 (*it)->draw();
      }
   }
   //cout << "after enemy\n";
   
   al_flip_display();
   //cout << "after display flip\n";
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
	 if (!(*it)->getdAnim_complete()) // if not dead (death animation not complete)
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
   Point pt(0, 0);
   Vector spd(0, 0);
   int n = rand() % 2 + 1;
   //int n = 1;
   switch(n) {
      case 1: // wave of 5
	 //spd.x = 0;
	 for (int i = 0; i < 5; i++) {
	    pt.rollRandom();
	    spd.rollRandom();
	    enem.push_back(make_shared<Enemy> (pt, al_map_rgb(246, 64, 234), spd));
	 }	 
	 break;
	 
      case 2: // wave of 8
	 for (int i = 0; i < 8; i++) {
	    pt.rollRandom();
	    spd.rollRandom();
	    enem.push_back(make_shared<Enemy> (pt, al_map_rgb(255, 159, 48), spd));
	 }
	 break;
   }
   
}
