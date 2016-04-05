/**
 * @file Single.cc
 * @brief Implementation of Single class- handles game interactions for 
 *        single player
 *
 * @author
 * @bug
 */
#include <iostream>
#include "Vector.h"
#include "Single.h"
#include "Projectile.h"
#include "Background.h"
#include "Enemy.h"
#include "Player.h"
#include "Laser.h"
#include "Missile.h"
#include "Sprite.h"
#include "Action.h"
using namespace act;

Single::~Single() {
   // clean up allegro timers
   if (gameOverTimer != NULL) al_destroy_timer(gameOverTimer);
   if (playerRespawn != NULL) al_destroy_timer(playerRespawn);
   if (playerWeapon1 != NULL) al_destroy_timer(playerWeapon1);
   if (playerWeapon2 != NULL) al_destroy_timer(playerWeapon2);
   al_destroy_font(gameOverFont);
   al_destroy_font(gameScoreFont);
   proj.clear();
   enem.clear();
   player.reset();
   bg.reset();
}

void Single::load_assets() {
   // initialize timers  
   if ((gameOverTimer = al_create_timer( 1.0 / framesPerSec )) == NULL) {
      std::cerr << "Cannot initialize game over timer\n";
      exit(1);
   }
    if ((upgradeText = al_create_timer( 1.0 / framesPerSec )) == NULL) {
      std::cerr << "Cannot initialize upgrade text timer\n";
      exit(1);
   }
   if ((playerRespawn = al_create_timer( 1.0 / framesPerSec )) == NULL) {
      std::cerr << "Cannot initialize player respawn timer\n";
      exit(2);
   }
   if ((playerWeapon1 = al_create_timer( 1.0 / framesPerSec )) == NULL) {
      std::cerr << "Cannot initialize player weapon timer\n";
      exit(3);
   }
   al_start_timer(playerWeapon1);

   if ((playerWeapon2 = al_create_timer( 1.0 / framesPerSec )) == NULL) {
      std::cerr << "Cannot initialize player weapon timer\n";
      exit(4);
   }
   al_start_timer(playerWeapon2);
  

   // create Player object
   setupPlayer();

   // specify path for assets to be loaded
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));
  
   // load various images
   bg = std::make_shared<Background> (Vector(50, 0), Vector(90, 0));
   playerShip = std::make_shared<Sprite> ("Sprite.png");

   // load font
   gameOverFont = al_load_font("DavidCLM-BoldItalic.ttf", 64, 0);
   gameScoreFont = al_load_font("ipag.ttf", 18, 0);
   
   // delete path to these assets now that they are loaded
   al_destroy_path(path);

}


// INPUT -----------------------------
void Single::input(ALLEGRO_KEYBOARD_STATE& kb) {
   if (player) {
      switch (player->input(kb)) {
	 case action::QUIT_GAME:
	    player.reset();
	    return;
	 case action::FIRE_PRIMARY:
	    if (al_get_timer_count(playerWeapon1) > 5 && playerScore<30) {
	       proj.push_back(std::make_shared<Laser> (player->centre, player->color,
						       player->projSpeed));	
	       al_stop_timer(playerWeapon1);
	       al_set_timer_count(playerWeapon1, 0);
	       al_start_timer(playerWeapon1);
	    }
	    if(al_get_timer_count(playerWeapon1) > 5 && playerScore>=30 && playerScore<100)
	    {
	       Point playerloc= player->centre;
	       playerloc.y=playerloc.y+(player->size/2);
	       proj.push_back(std::make_shared<Laser> (playerloc, player->color,
						       player->projSpeed));
	       playerloc.y=playerloc.y-player->size;
	       proj.push_back(std::make_shared<Laser> (playerloc, player->color,
						       player->projSpeed));
	       al_stop_timer(playerWeapon1);
	       al_set_timer_count(playerWeapon1, 0);
	       al_start_timer(playerWeapon1);
	    }
	    if(al_get_timer_count(playerWeapon1) > 5 && playerScore>=100)
	    {
	       Point playerloc= player->centre;
	       playerloc.y=playerloc.y+(player->size/2);
	       proj.push_back(std::make_shared<Laser> (playerloc, player->color,
						       player->projSpeedD));
	       playerloc.y=playerloc.y-player->size;
	       proj.push_back(std::make_shared<Laser> (playerloc, player->color,
						       player->projSpeedU));
	       proj.push_back(std::make_shared<Laser> (player->centre, player->color, player->projSpeed));
	       al_stop_timer(playerWeapon1);
	       al_set_timer_count(playerWeapon1, 0);
	       al_start_timer(playerWeapon1);
	    }
	       break;
	       case action::FIRE_SECONDARY:
	    if (al_get_timer_count(playerWeapon2) > 20) {
	       proj.push_back(std::make_shared<Missile> (player->centre, player->color,
							 player->projSpeed));
	       al_stop_timer(playerWeapon2);
	       al_set_timer_count(playerWeapon2, 0);
	       al_start_timer(playerWeapon2);
	    }
	 default:
	    break;
      }
   }
}

bool Single::is_game_over() {
   return (al_get_timer_count(gameOverTimer) >= 80) && gameOver;
}


void Single::update(double dt) {
   updateBackgroundPosition(dt);
   if (player) player->update(dt);
   else if (!player && playerLives <= 0) gameOver = true;
   else respawnPlayer();
   updateProjectilePosition(dt);
   updateEnemyPosition(dt);   
   collision();
   clean();      
}

void Single::draw() {
   drawBackground();
   drawLives();
   drawScore();
   drawWeaponUp();
   if (gameOver) showGameOverMessage();
   else if (player) player->draw(playerShip);
   drawProjectiles();
   drawEnemies();
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

void Single::respawnPlayer() {
   if (!al_get_timer_started(playerRespawn))
      al_start_timer(playerRespawn);
   
   if (al_get_timer_count(playerRespawn) > 80) {
      setupPlayer();
      al_stop_timer(playerRespawn);
      al_set_timer_count(playerRespawn, 0);
   }
}


void Single::drawLives() {
   if (playerLives > 0)
      al_draw_rectangle(displayWidth - 70, 50, displayWidth - 50, 70,
			al_map_rgb(0, 255, 0), 5);
   if (playerLives > 1)
      al_draw_rectangle(displayWidth - 110, 50, displayWidth - 90, 70,
			al_map_rgb(0, 255, 0), 5);
   if (playerLives > 2)
      al_draw_rectangle(displayWidth - 150, 50, displayWidth - 130, 70,
			al_map_rgb(0, 255, 0) , 5);
   if (!player && playerLives > 0) {
      al_draw_textf(gameOverFont, al_map_rgb(255, 0, 0), 400, 300,
		    ALLEGRO_ALIGN_CENTRE,
		    "%i LIVES REMAINING",
		    playerLives);      
   }
}
void Single::drawWeaponUp(){
   if(playerScore>=30)
   {
      if (!al_get_timer_started(upgradeText))
      { al_start_timer(upgradeText);}
      if(al_get_timer_count(upgradeText)<100){
	 al_draw_text(gameScoreFont, al_map_rgb(255, 255, 255), 400, 65,
		      ALLEGRO_ALIGN_CENTRE, "WEAPON UPGRADED");
      }
      //al_stop_timer(upgradeText); 
   }
   //al_stop_timer(upgradeText);

}

void Single::drawScore() {
   al_draw_textf(gameScoreFont, al_map_rgb(255, 255, 255), 100, 100,
   		 ALLEGRO_ALIGN_CENTRE, "Score: %i", playerScore);   
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

// where p1 is the point, p2 is the centre of the 'box' object, with half of 
// its width s2
bool Single::isPointBoxCollision(const Point& p1, const Point& p2, 
				 const int& s2) {
   return ((p1.x > p2.x - s2) &&
	   (p1.x < p2.x + s2) &&
	   (p1.y > p2.y - s2) &&
	   (p1.y < p2.y + s2));
}

void Single::checkCollisionOnPlayer() {
   if (!proj.empty() && player) {
      for (std::list< std::shared_ptr<Projectile> >::iterator it_proj = 
	      proj.begin(); it_proj != proj.end(); ++it_proj) {	    
	 // check if projectile color is different from player color
	 if (!doColorsMatch((*it_proj)->color, player->color)) {
	    if (isPointBoxCollision((*it_proj)->centre,
				    player->centre, player->size)) {	  
	       // register damage on player and flag projectile as dead
	       (*it_proj)->live = false;
	       player->hit(1);
	    }
	 }
      }
   }  
}

bool Single::doColorsMatch(const ALLEGRO_COLOR& a, const ALLEGRO_COLOR& b) {
   return (a.r == b.r && a.g == b.g && a.b == b.b);
}

void Single::checkCollisionOnEnemies() {
   if (!proj.empty() && !enem.empty() && player) {
      // set player color for which we will be checking for
      for (std::list< std::shared_ptr<Projectile> >::iterator it_proj = 
	      proj.begin(); it_proj != proj.end(); ++it_proj) {
	    
	 // check if colors match
	 if (doColorsMatch(player->color, (*it_proj)->color)) {
	    for (std::list< std::shared_ptr<Enemy> >::iterator it_enem = 
		    enem.begin(); it_enem != enem.end(); ++it_enem) {
		  
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
		     updateScore(player->color);
		  
	       }
	    }
	 }
      }
    
   }
}

void Single::checkCollidingEnemyWithPlayer() {
   if (!enem.empty() && player) {
      for (std::list< std::shared_ptr<Enemy> >::iterator it_enem = enem.begin();
	   it_enem != enem.end(); ++it_enem) {
	 if (!(*it_enem)->getDead()){
	 if (doHitboxesIntersect(player->centre, player->size,
				 (*it_enem)->getCentre(), 
				 (*it_enem)->getSize())) {
	    // collision - register damage
	    (*it_enem)->hit();
	    player->hit(1);
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


void Single::updateScore(ALLEGRO_COLOR& c) {
   if (player) 
      if (doColorsMatch(player->color, c))
	 playerScore += 1;
}



void Single::spawn() {
   // some initializations 
   Point pt(0, 0);
   Point pt1, pt2, playerloc, pt3;
   Vector spd(0, 0);
   ALLEGRO_COLOR color = al_map_rgb(255,255,255);

   
   if (player)
      playerloc = player->centre;
   else
      playerloc = Point (200, 300);

   // roll for enemy routine
   int n = rand() % 6 + 1;

   // select enemy routine
   switch(n) {

      case 1: // wave of 5
	 for (int i = 0; i < 5; i++) {
	    pt.rollRandom();
	    spd.rollRandom();
	    enem.push_back(std::make_shared<Enemy> (pt, al_map_rgb(255, 51, 51), 
						    spd));
	 }	 
	 break;

	 
      case 2: // wave of 8
	 for (int i = 0; i < 8; i++) {
	    pt.rollRandom();
	    spd.rollRandom();
	    enem.push_back(std::make_shared<Enemy> (pt, al_map_rgb(255, 159, 48), 
						    spd));
	 }
	 break;

	 
      case 3:
	 enem.push_back(std::make_shared<Enemy> (Point(800, 300), 
						 al_map_rgb(246, 64, 234),
						 Vector(-180, 0)));
	 enem.push_back(std::make_shared<Enemy> (Point(900, 350), 
						 al_map_rgb(246, 64, 234),
						 Vector(-180, 0)));
	 enem.push_back(std::make_shared<Enemy> (Point(900, 250), 
						 al_map_rgb(246, 64, 234),
						 Vector(-180, 0)));
	 enem.push_back(std::make_shared<Enemy> (Point(1000, 400), 
						 al_map_rgb(246, 64, 234),
						 Vector(-180, 0)));
	 enem.push_back(std::make_shared<Enemy> (Point(1000, 200), 
						 al_map_rgb(246, 64, 234),
						 Vector(-180, 0)));
	 enem.push_back(std::make_shared<Enemy> (Point(1100, 100), 
						 al_map_rgb(246, 64, 234),
						 Vector(-180, 0)));
	 enem.push_back(std::make_shared<Enemy> (Point(1100, 500), 
						 al_map_rgb(246, 64, 234),
						 Vector(-180, 0)));
	 break;
	 
      case 4:
	 pt1.x=800; pt1.y=580;
	 pt2.x=800; pt2.y=20;
	 pt3.x=850; pt3.y=300;
	 enem.push_back(std::make_shared<Enemy>
			(pt1, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt1.x)/1.5),
							       ((playerloc.y-pt1.y)/1.5))));
	 enem.push_back(std::make_shared<Enemy>	    
			(pt2, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt2.x)/1.5),
							       ((playerloc.y-pt2.y)/1.5))));
	 enem.push_back(std::make_shared<Enemy>
			(pt3, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt3.x)/1.5),
							       ((playerloc.y-pt3.y)/1.5))));
	 break;

	 
      case 5:
	 spawn();
	 spawn();
	 break;

	 
      case 6:
	 color = al_map_rgb(255, 153, 255);
	 for(int i=0; i<5; i++) {
	    spd.rollReallyRandom();
	    enem.push_back(std::make_shared<Enemy> (Point(800, 300), color, spd));
	 }
	 break;
   }
   
}

// HELPER FUNCTIONS GO DOWN HERE


void Single::updateProjectilePosition(double dt) {
   if (!proj.empty()) {
      for (std::list< std::shared_ptr<Projectile> >::iterator it = proj.begin(); 
	   it != proj.end(); ++it) {
	 (*it)->update(dt);
      }
   }
}

void Single::updateEnemyPosition(double dt) {
   if (!enem.empty()) {
      for (std::list< std::shared_ptr<Enemy> >::iterator it = enem.begin(); 
	   it != enem.end(); ++it) {
	 (*it)->update(dt);
	 if((*it)->getFire()){
	    proj.push_back(std::make_shared<Laser> ((*it)->getCentre(), 
						    (*it)->getColor(),
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



void Single::drawProjectiles() {
   if (!proj.empty()) {
      for (std::list< std::shared_ptr<Projectile> >::iterator it = proj.begin(); 
	   it != proj.end(); ++it) { 
	 (*it)->draw();
      }
   }
}

void Single::drawEnemies() {
   if (!enem.empty()) {
      for (std::list< std::shared_ptr<Enemy> >::iterator it = enem.begin(); 
	   it != enem.end(); ++it) {
	 (*it)->draw();
      }
   }
}

void Single::drawBackground() {
   bg->draw();
}
void Single::setupPlayer() {
   player = std::make_shared<Player> (Point(215, 245),
				      al_map_rgb(0,200,0));
}

void Single::cullPlayer() {
   if (player) {
      if (player->dead) {
	 playerLives -= 1;
	 player.reset();
      }
   }
}

void Single::cullProjectiles() {
   std::list< std::shared_ptr<Projectile> > newProj;
   if (!proj.empty()) {
      for (std::list< std::shared_ptr<Projectile> >::iterator it = proj.begin(); 
	   it != proj.end(); ++it) {
	 if ((*it)->live) // if live
	    newProj.push_back(*it);
      }
      proj.clear();
      proj.assign(newProj.begin(), newProj.end());      
   }
}

void Single::cullEnemies() {
   std::list< std::shared_ptr<Enemy> > newEnem;
   if (!enem.empty()) {
      for (std::list< std::shared_ptr<Enemy> >::iterator it = enem.begin(); 
	   it != enem.end(); ++it) {
	 if (!(*it)->getdAnim_complete()) 
	    // if not dead (death animation not complete)
	    newEnem.push_back(*it);
      }
      enem.clear();
      enem.assign(newEnem.begin(), newEnem.end());      
   }
}

