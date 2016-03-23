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
   // initialize gameOverTimer
   gameOverTimer = al_create_timer( 1.0 / fps );
   
   // create Player object
   setupPlayer();

   // specify path for assets to be loaded
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));

   // load background
   setupBackground();

   // load font
   gameOverFont = al_load_font("DavidCLM-BoldItalic.ttf", 64, 0);

   // delete path to these assets now that they are loaded
   al_destroy_path(path);
}

bool Single::is_game_over() {
   return (al_get_timer_count(gameOverTimer) >= 80);
}

void Single::showGameOverMessage() {
   if (!al_get_timer_started(gameOverTimer))
      al_start_timer(gameOverTimer);
   
   if (al_get_timer_count(gameOverTimer) < 80) {
      al_draw_text(gameOverFont, al_map_rgb(255, 0, 0), 400, 300,
		   ALLEGRO_ALIGN_CENTRE,
		   "GAME OVER");
   }
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

void Single::collision() {
   checkCollisionOnPlayer();
   checkCollisionOnEnemies();
   checkCollidingEnemyWithPlayer();
}

void Single::updatePlayerAction() {
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

// where p1 is the point, p2 is the centre of the 'box' object, with half of its width s2
bool Single::isPointBoxCollision(const Point& p1, const Point& p2, const int& s2) {
   return ((p1.x > p2.x - s2) &&
	   (p1.x < p2.x + s2) &&
	   (p1.y > p2.y - s2) &&
	   (p1.y < p2.y + s2));
}

void Single::checkCollisionOnPlayer() {
   if (!proj.empty() && !play.empty()) {
      for (list< shared_ptr<Player> >::iterator it_play = play.begin();
	   it_play != play.end(); ++it_play) {
	 for (list< shared_ptr<Projectile> >::iterator it_proj = proj.begin();
	      it_proj != proj.end(); ++it_proj) {	    
	    // check if projectile color is different from player color
	    if (!doColorsMatch((*it_proj)->color, (*it_play)->color)) {
	       if (isPointBoxCollision((*it_proj)->centre,
				       (*it_play)->centre, (*it_play)->size)) {		  
		  // register damage on player and flag projectile as dead
		  (*it_proj)->live = false;
		  (*it_play)->hit(1);
	       }
	    }
	 }
      }
   }
}

bool Single::doColorsMatch(const ALLEGRO_COLOR& a, const ALLEGRO_COLOR& b) {
   return (a.r == b.r && a.g == b.g && a.b == b.b);
}

void Single::checkCollisionOnEnemies() {
   if (!proj.empty() && !enem.empty() && !play.empty()) {
      for (list< shared_ptr<Player> >::iterator it_play = play.begin();
	   it_play != play.end(); ++it_play) {
	 
	 // set player color for which we will be checking for
	 ALLEGRO_COLOR play_color = (*it_play)->color;
	 
	 for (list< shared_ptr<Projectile> >::iterator it_proj = proj.begin();
	      it_proj != proj.end(); ++it_proj) {
	    
	    // check if colors match
	    if (doColorsMatch(play_color, (*it_proj)->color)) {
	       for (list< shared_ptr<Enemy> >::iterator it_enem = enem.begin();
		    it_enem != enem.end(); ++it_enem) {
		  
		  // set bounding points
		  Point pt_proj = (*it_proj)->centre;
		  Point pt_enem = (*it_enem)->getCentre();
		  int enem_size = (*it_enem)->getSize();
		  
		  // check for collision
		  if ((pt_proj.x > pt_enem.x - enem_size) &&
		      (pt_proj.x < pt_enem.x + enem_size) &&
		      (pt_proj.y > pt_enem.y - enem_size) &&
		      (pt_proj.y < pt_enem.y + enem_size)) {
		     
		     // register damage on enemy and flag projectile as dead
		     (*it_proj)->live = false;
		     (*it_enem)->hit();
		     
		     // check for enemy death, update score if true
		     if ((*it_enem)->getDead())
			updateScore(play_color);
		  
		  }
	       }
	    }
	 }
      }
   }
}

void Single::checkCollidingEnemyWithPlayer() {
   if (!enem.empty() && !play.empty()) {
      for (list< shared_ptr<Player> >::iterator it_play = play.begin();
	   it_play != play.end(); ++it_play) {
	 for (list< shared_ptr<Enemy> >::iterator it_enem = enem.begin();
	      it_enem != enem.end(); ++it_enem) {
	    if (doHitboxesIntersect((*it_play)->centre, (*it_play)->size,
				    (*it_enem)->getCentre(), (*it_enem)->getSize())) {
	       // collision - register damage
	       (*it_enem)->hit();
	       (*it_play)->hit(1);
		
	    }	       
	 }
      }
   }
}

bool Single::doHitboxesIntersect(const Point& centre1, const int& size1,
				 const Point& centre2, const int& size2) {
   return (abs(centre1.x - centre2.x) < (size1 + size2) &&
	   abs(centre1.y - centre2.y) < (size1 + size2));
}


void Single::updateScore(const ALLEGRO_COLOR& c) {
   if (!play.empty()) {
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
	 if (doColorsMatch((*it)->color, c)) {
	    (*it)->score += 1;
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
   //al_start_timer(spawnDelay);
   Point pt(0, 0);
   Point pt1, pt2, playerloc, pt3;
   Vector spd(0, 0);
   ALLEGRO_COLOR color = al_map_rgb(255,255,255);
   if(!play.empty())
      for (list< shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) 
	 playerloc = (*it)->centre;
   if(play.empty())
      playerloc = Point (200, 300);
   
   int n = rand() % 6 + 1;
   switch(n) {
      case 1: // wave of 5
	 //spd.x = 0;
	 for (int i = 0; i < 5; i++) {
	    pt.rollRandom();
	    spd.rollRandom();
	    enem.push_back(make_shared<Enemy> (pt, al_map_rgb(255, 51, 51), spd));
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
					    Vector(-180, 0)));
	 enem.push_back(make_shared<Enemy> (Point(900, 350), al_map_rgb(246, 64, 234),
					    Vector(-180, 0)));
	 enem.push_back(make_shared<Enemy> (Point(900, 250), al_map_rgb(246, 64, 234),
					    Vector(-180, 0)));
	 enem.push_back(make_shared<Enemy> (Point(1000, 400), al_map_rgb(246, 64, 234),
					    Vector(-180, 0)));
	 enem.push_back(make_shared<Enemy> (Point(1000, 200), al_map_rgb(246, 64, 234),
					    Vector(-180, 0)));
	 enem.push_back(make_shared<Enemy> (Point(1100, 100), al_map_rgb(246, 64, 234),
					    Vector(-180, 0)));
	 enem.push_back(make_shared<Enemy> (Point(1100, 500), al_map_rgb(246, 64, 234),
					    Vector(-180, 0)));
	 break;
	 
      case 4:
	 //std::cout<<"play loc is "<<playerloc.x<<" "<<playerloc.y<<std::endl;
	 pt1.x=800; pt1.y=580;
	 pt2.x=800; pt2.y=20;
	 pt3.x=850; pt3.y=300;
	 //std::cout<<"velocity is "<<spd.x<<" "<<spd.y<<std::endl;
	 enem.push_back(
	    make_shared<Enemy>
	    (pt1, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt1.x)/1.5),
						   ((playerloc.y-pt1.y)/1.5))));
	 enem.push_back(
	    make_shared<Enemy>	    
	    (pt2, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt2.x)/1.5),
						   ((playerloc.y-pt2.y)/1.5))));
	 enem.push_back(
	    make_shared<Enemy>
	    (pt3, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt3.x)/1.5),
						   ((playerloc.y-pt3.y)/1.5))));
	 break;
      case 5:
	 spawn();
	 spawn();
	 break;
      case 6:
	 color=al_map_rgb(255,153,255);
	 for(int i=0; i<5; i++)
	 {
	    spd.rollReallyRandom();
	    enem.push_back(make_shared<Enemy>(Point(800, 300), color, spd));
	 }
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
   if(enem.size() <= 2)
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
   play.push_back(make_shared<Player> (Point(215, 245),
				       al_map_rgb(0,200,0), h,
				       fps ));
}

void Single::setupBackground() {
   bg = make_shared<Background> (Vector(-50, 0), Vector(-90, 0));
}

void Single::cullPlayer() {
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
