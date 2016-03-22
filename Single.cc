/**
 * @file Single.cc
 * @brief Implementation of Single class- handles game interactions for single player
 *
 * @author
 * @bug
 */
#include "Single.h"

Single::~Single() {
   al_destroy_font(gameOverFont);
   al_destroy_timer(gameOverTimer);
   proj.clear();
   enem.clear();
   play.clear();
   bg = NULL;
}

void Single::load_assets() {
   gameOverTimer = al_create_timer( 1.0 / 30.0 );
   
   setupPlayer();   
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
   
   setupBackground();
   gameOverFont = al_load_font("DavidCLM-BoldItalic.ttf", 64, 0);
   
   al_destroy_path(path);
}

bool Single::is_game_over() {
   if (al_get_timer_count(gameOverTimer) >= 80)
      return true;      
   return false;
}

void Single::showGameOverMessage() {
   if (!al_get_timer_started(gameOverTimer))
      al_start_timer(gameOverTimer);
   if (al_get_timer_count(gameOverTimer) < 80) 
      al_draw_text(gameOverFont, al_map_rgb(255, 0, 0), 400, 300, ALLEGRO_ALIGN_CENTRE,
		   "GAME OVER - YOU SUCK");   
   else 
      al_stop_timer(gameOverTimer);
   
}

void Single::update(double dt) {
   updatePlayerAction();   
   updateBackgroundPosition(dt);
   updatePlayerPosition(dt);
   updateProjectilePosition(dt);
   updateEnemyPosition(dt);   
   collision();
   clean();      
}

void Single::draw() {
   //al_clear_to_color(al_map_rgb(0, 0, 0));
   drawBackground();
   drawPlayer();
   drawProjectiles();
   drawEnemies();
   if (play.empty()) 
      showGameOverMessage();   
   al_flip_display();
}

void Single::clean() {
   cullPlayer();
   cullProjectiles();
   cullEnemies();
}


void Single::updatePlayerAction() {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->updatePlayerSpeed();	 
	 if ((*it)->getFire()) {
	    proj.push_back(make_shared<Laser> ((*it)->getCentre(), (*it)->getColor(),
					       (*it)->getProjSpeed()));
	    (*it)->setFire(false);
	 }
	 
	 if ((*it)->getmFire()) {
	    proj.push_back(make_shared<Missile> ((*it)->getCentre(), (*it)->getColor(),
						 (*it)->getProjSpeed()));
	    (*it)->setmFire(false);
	 }
	 
      }
   }
}


void Single::collision() {
   if (!proj.empty()) {
      for (list< shared_ptr<Projectile> >::iterator i = proj.begin(); i != proj.end(); ++i) {
	 if (!play.empty()) {
	    for (list< shared_ptr<Player> >::iterator p = play.begin(); p != play.end(); ++p) {
	       Point A = (*i)->centre;
	       Point B = (*p)->getCentre(); int b = (*p)->getSize();
	       if ((A.x > B.x - b) && (A.x < B.x + b) &&
		   (A.y > B.y - b) && (A.y < B.y + b)) {
		  // is a hit on Player
		  (*i)->live = false;
		  (*p)->hit(1); // reduce player life
		  
	       }	    
	    }
	 }
	 
	 // check against enemies
	 if (!enem.empty()) {
	    for (list< shared_ptr<Enemy> >::iterator e = enem.begin(); e != enem.end(); ++e) {
	       Point A = (*i)->centre;
	       Point B = (*e)->getCentre(); int b = (*e)->getSize();
	       if ((A.x > B.x - b) &&
		   (A.x < B.x + b) &&
		   (A.y > B.y - b) &&
		   (A.y < B.y + b)) {
		  // is a hit on Enemy
		  (*i)->live = false;
		  (*e)->hit();
		  if ((*e)->getDead())
		     updateScore((*i)->color);
	       }
	    }
	 }
      }
   }
   //check collision on enemy bodies vs player
   if(!enem.empty()){
      for(list<shared_ptr<Enemy>>:: iterator i=enem.begin(); i!=enem.end(); ++i){
	 if(!play.empty()){
	    for(list<shared_ptr<Player>>::iterator p=play.begin();p!=play.end(); ++p){
	       Point A=(*i)->getCentre();
	       Point B=(*p)->getCentre(); int b=(*p)->getSize();
	       if((A.x>B.x-b)&&(A.x<B.x+ b)&&
		  (A.y>B.y-b)&&(A.y<B.y+b))
	       {
		  (*i)->hit();
		  (*p)->hit(1);
	       }
	    }
	 }
      }
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

void Single::input(const ALLEGRO_EVENT& inputEvent) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->input(inputEvent);
      }
   }
}

void Single::spawn() {
   ALLEGRO_TIMER *spawnDelay;
   if((spawnDelay=al_create_timer(1.0/30.0))==NULL)
      throw std::runtime_error("cannot create spawnDelay timer");
   //al_start_timer(spawnDelay);
   Point pt(0, 0);
   Point pt1, pt2, pt3, playerloc;
   Vector spd(0, 0);
   if(!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 playerloc= (*it)->getCentre();
   if(play.empty())
      playerloc=Point (200, 300);
   
   int n = rand() % 5 + 1;
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
	 
      case 3:
      	 enem.push_back(make_shared<Enemy> (Point(800, 300), al_map_rgb(246, 64, 234),
					    Vector(-150, 0)));
	 enem.push_back(make_shared<Enemy> (Point(900, 350), al_map_rgb(246, 64, 234),
					    Vector(-150, 0)));
	 enem.push_back(make_shared<Enemy> (Point(900, 250), al_map_rgb(246, 64, 234),
					    Vector(-150, 0)));
	 enem.push_back(make_shared<Enemy> (Point(1000, 400), al_map_rgb(246, 64, 234),
					    Vector(-150, 0)));
	 enem.push_back(make_shared<Enemy> (Point(1000, 200), al_map_rgb(246, 64, 234),
					    Vector(-150, 0)));
	 enem.push_back(make_shared<Enemy> (Point(1100, 100), al_map_rgb(246, 64, 234),
					    Vector(-150, 0)));
	 enem.push_back(make_shared<Enemy> (Point(1100, 500), al_map_rgb(246, 64, 234),
					    Vector(-150, 0)));
	 break;
	 
      case 4:
	 //std::cout<<"play loc is "<<playerloc.x<<" "<<playerloc.y<<std::endl;
	 
	 pt1.x=800; pt1.y=590;
	 pt2.x=800; pt2.y=10;
	 pt3.x=900; pt3.y=300;
	 //std::cout<<"velocity is "<<spd.x<<" "<<spd.y<<std::endl;
	 enem.push_back(
	    make_shared<Enemy>
	    (pt1, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt1.x)/1.4),
						   ((playerloc.y-pt1.y)/1.4))));
	 enem.push_back(
	    make_shared<Enemy>
	    (pt2, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt2.x)/1.4),
						   ((playerloc.y-pt2.y)/1.4))));
	 enem.push_back(
	    make_shared<Enemy>
	    (pt3, al_map_rgb(255, 255, 255), Vector(((playerloc.x-pt3.x)/1.4),
						   ((playerloc.y-pt3.y)/1.4))));
	 break;
      case 5:
	 spawn();
	 spawn();
	 
   }
   
}

// HELPER FUNCTIONS GO DOWN HERE
void Single::updatePlayerPosition(double dt) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->update(dt);
      }
   }
}

void Single::updateProjectilePosition(double dt) {
   if (!proj.empty()) {
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) {
	 (*it)->update(dt);
      }
   }
}

void Single::updateEnemyPosition(double dt) {
   if (!enem.empty()) {
      for (list< shared_ptr<Enemy> >::iterator it = enem.begin(); it != enem.end(); ++it) {
	 (*it)->update(dt);
	 if((*it)->getFire()){
	    proj.push_back(make_shared<Laser> ((*it)->getCentre(), (*it)->getColor(),
					       (*it)->getProjSpeed()));
	    (*it)->setFire(false);	    
	 }	 	 
      }
   }
   if(enem.size()<=2)
      spawn();
}

void Single::updateBackgroundPosition(double dt) {
   bg->update(dt);
}

void Single::drawPlayer() {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 (*it)->draw();
      }
   }
}

void Single::drawProjectiles() {
   if (!proj.empty()) {
      for (list< shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it){ 
	 (*it)->draw();
      }
   }
}

void Single::drawEnemies() {
   if (!enem.empty()) {
      for (list< shared_ptr<Enemy> >::iterator it = enem.begin(); it != enem.end(); ++it) {
	 (*it)->draw();
      }
   }
}

void Single::drawBackground() {
   bg->draw();
}
void Single::setupPlayer() {
   vector<int> h;
   h.push_back(ALLEGRO_KEY_W);
   h.push_back(ALLEGRO_KEY_S);
   h.push_back(ALLEGRO_KEY_D);
   h.push_back(ALLEGRO_KEY_A);
   play.push_back(make_shared<Player> (Point(200, 300),
				       al_map_rgb(0,200,0), h,
				       false, fps ));
}

void Single::setupBackground() {
   //initializes background images, vectors decide 'parallax' speed
   bg = make_shared<Background> (Vector(-50, 0), Vector(-90, 0));
}

void Single::cullPlayer() {
   list< shared_ptr<Player> > newPlay;
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 if (!(*it)->getDead()) // if not dead
	    newPlay.push_back(*it);
      }
      play.clear();
      play.assign(newPlay.begin(), newPlay.end());      
   }   
}

void Single::cullProjectiles() {
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

void Single::cullEnemies() {
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
