/**
 * @file Single.cc
 * @brief Implementation of Single class- handles game interactions for 
 *        single player
 *
 * @author
 * @bug
 */
#include "Single.h"

#include <iostream>

#include "Point.h"
#include "Vector.h"
#include "Projectile.h"
#include "Player.h"
#include "Laser.h"
#include "Missile.h"
#include "Sprite.h"

#include "Action.h"
#include "Timer.h"
#include "Font.h"

#include "Enemy.h"
#include "Creep.h"
#include "CreepBomb.h"
#include "Boss.h"

using namespace act;

const int GAME_OVER_WAIT_TIME = 80;
const int WEAPON_DELAY_LASER = 6;
const int WEAPON_DELAY_MISSILE = 20;
const Vector PLAYER_PROJECTILE_SPEED = Vector(500, 0);

// constructor
Single::Single(int w, int h, int f) : Root(w, h, f), gameOver(false), playerLives(3),
				      playerScoreTotal(0), playerScore(0)
{
   //std::cout << "in the single constructor\n";
}

// destructor
Single::~Single() {
   //std::cout << "in the single destructor\n";
   player.reset();
   bg.reset();
   proj.clear();
   enem.clear();

   gameOverTimer.reset();
   playerWeapon1.reset();
   playerWeapon2.reset();
   playerRespawn.reset();
   upgradeText.reset();
}

// initialize Single player mode
void Single::init() {
   //std::cout << "in single init function\n";
   // timers
   gameOverTimer = std::make_shared<Timer> (framesPerSec); gameOverTimer->create();
   playerWeapon1 = std::make_shared<Timer> (framesPerSec); playerWeapon1->create();   
   playerWeapon2 = std::make_shared<Timer> (framesPerSec); playerWeapon2->create();
   playerRespawn = std::make_shared<Timer> (framesPerSec); playerRespawn->create();
   upgradeText = std::make_shared<Timer> (framesPerSec); upgradeText->create();
   //std::cout << "in single init, after timer creation\n";
   playerWeapon1->startTimer();
   playerWeapon2->startTimer();
   //std::cout << "timers have been started\n";
   // create Player object
   setupPlayer();
   // go to resources directory
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));   
   // fonts
   gameOverFont = std::make_shared<Font> ("DavidCLM-BoldItalic.ttf", 64); gameOverFont->load();
   gameScoreFont = std::make_shared<Font> ("ipag.ttf", 18); gameScoreFont->load();   
   // background
   bg = std::make_shared<Background> (Vector(50, 0), Vector(-90, 0));
   // sprites
   playerShip = std::make_shared<Sprite> ("Sprite.png");
   enemyShip = std::make_shared<Sprite> ("EnemyBasic.png");
   enemyDeath = std::make_shared<Sprite> ("explode.png");
   enemyBomb = std::make_shared<Sprite> ("spikebomb.png");
   // delete path 
   al_destroy_path(path);
   //std::cout << "end of single init \n";
}

// INPUT -----------------------------
void Single::input(ALLEGRO_KEYBOARD_STATE& kb) {
   if (player) {
      switch (player->input(kb)) {	 
	 case action::QUIT_GAME: // player indicated they wish to quit the game
	    player.reset();
	    return;	    
	 case action::FIRE_PRIMARY:
	    
	    // single
	    if (playerWeapon1->getCount() > WEAPON_DELAY_LASER &&
		playerScore < 30) {
	       
	       addLaser(player->centre + Point(-20, 0), player->color, PLAYER_PROJECTILE_SPEED);
	       playerWeapon1->stopTimer();
	       playerWeapon1->resetCount();
	       playerWeapon1->startTimer();
	    }
	    
	    // double
	    else if (playerWeapon1->getCount() > WEAPON_DELAY_LASER+4 &&
		playerScore >= 30 && playerScore < 100) {

	       addLaser(player->centre + Point(-25, 10), player->color,
			PLAYER_PROJECTILE_SPEED);
	       addLaser(player->centre + Point(-25, -10), player->color,
			PLAYER_PROJECTILE_SPEED);
	       
	       playerWeapon1->stopTimer();
	       playerWeapon1->resetCount();
	       playerWeapon1->startTimer();
	    }
	    
	    // triple
	    else if (playerWeapon1->getCount() > WEAPON_DELAY_LASER+6 &&
		playerScore >= 100) {

	       addLaser(player->centre, player->color, PLAYER_PROJECTILE_SPEED);
	       addLaser(player->centre + Point(0, 5), player->color,
			Vector(0, 75) + PLAYER_PROJECTILE_SPEED);
	       addLaser(player->centre + Point(0, -5), player->color,
			Vector(0, -75) + PLAYER_PROJECTILE_SPEED);
	       
	       playerWeapon1->stopTimer();
	       playerWeapon1->resetCount();
	       playerWeapon1->startTimer();
	    }
	    break;
	 case action::FIRE_SECONDARY:	    	    
	    if (playerWeapon2->getCount() > WEAPON_DELAY_MISSILE) {
	       
	       addMissile(player->centre, player->color, PLAYER_PROJECTILE_SPEED);

	       playerWeapon2->stopTimer();
	       playerWeapon2->resetCount();
	       playerWeapon2->startTimer();
	    }
	    break;
	 default:
	    break;
      }
   }
}

// returns the total score the player has accumulated for the game
int Single::getScore() const {
   return playerScoreTotal;
}

// function to add a Laser object onto the Projectile list
void Single::addLaser(const Point& cen, const ALLEGRO_COLOR& col, const Vector& spd) {
   proj.push_back(std::make_shared<Laser> (cen, col, spd));
}

// function to add a Missile object onto the Projectile list
void Single::addMissile(const Point& cen, const ALLEGRO_COLOR& col, const Vector& spd) {
   std::shared_ptr<Projectile> missileObject = std::make_shared<Missile> (cen, col, spd);
   missileObject->load_assets();
   proj.push_back(missileObject);
}

// function to add a Creep object onto the Enemy list
void Single::addCreep(const Point& cen, const ALLEGRO_COLOR& col, const Vector& spd) {
   enem.push_back(std::make_shared<Creep> (cen, col, spd));
}

// function to add a CreepBomb object onto the Enemy list
void Single::addCreepB(const Point& cen, const ALLEGRO_COLOR& col, const Vector& spd) {
   enem.push_back(std::make_shared<CreepBomb>(cen, col, spd));
}

// returns true if the gameOver is true and if the game over screen has completed
// its duration
bool Single::is_game_over() const {
   return (gameOverTimer->getCount() >= GAME_OVER_WAIT_TIME) && gameOver;
}

// performs an update for all the necessary game logic
void Single::update(double dt) {
   bg->update(dt);
   if (player) player->update(dt);
   else if (!player && playerLives <= 0) gameOver = true;
   else respawnPlayer();
   
   updateProjectilePosition(dt);
   updateEnemyPosition(dt);   
   collision();
   clean();      
}

// renders the entire scene
void Single::draw() {
   bg->draw();
   drawLives();
   // gameScoreFont->drawTextF(al_map_rgb(255, 255, 255), 100, 100, "Score: %i",
   // playerScoreTotal);
   
   drawEnemies(); // calls draw on each enemy, provides Sprite pointer
   drawProjectiles();   
   if (gameOver) showGameOverMessage();
   else if (player) player->draw(playerShip, 0);
   gameScoreFont->drawTextF(al_map_rgb(255, 255, 255), 100, 50,"Score: %i", playerScoreTotal);
   drawWeaponUpgradeStatus();
}


void Single::showGameOverMessage() {
   if (!gameOverTimer->isRunning())
      gameOverTimer->startTimer();   
   if (gameOverTimer->getCount() < 80) {
      gameOverFont->drawTextCentered(al_map_rgb(255, 0, 0), "GAME OVER");
   }
   
   else {
      gameOverTimer->stopTimer();
   }
}

void Single::respawnPlayer() {
   if (!playerRespawn->isRunning())
      playerRespawn->startTimer();
   
   if (playerRespawn->getCount() > 80) {
      setupPlayer();
      playerRespawn->stopTimer();
      playerRespawn->resetCount();
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
      gameOverFont->drawTextCenteredF(al_map_rgb(255, 0, 0), "%i LIVES REMAINING", playerLives);
   }
}
void Single::drawWeaponUpgradeStatus(){
   
   al_draw_rounded_rectangle(displayWidth - (displayWidth/2)-50, 50,
			     displayWidth-(displayWidth/2)+50,
			     70, 2, 2, al_map_rgb(255, 255, 255), 1);
   if(playerScore!=0){
      if(playerScore<30)
	 al_draw_filled_rounded_rectangle(displayWidth - (displayWidth/2)-49, 51, displayWidth-
					  (displayWidth/2)-49+playerScore*3.3, 69, 2, 2,
					  al_map_rgb(255, 0, 0));
      if(playerScore >= 30 && playerScore <100){
	 al_draw_filled_rounded_rectangle(displayWidth - (displayWidth/2)-49, 51, displayWidth-
					  (displayWidth/2)-49+(playerScore-30)*1.428, 69, 2, 2,
					  al_map_rgb(255, 0, 0));}
      if(playerScore>=100){
	 al_draw_filled_rounded_rectangle(displayWidth - (displayWidth/2)-49, 51, displayWidth-
					  (displayWidth/2)+49, 69, 2, 2, al_map_rgb(0, 255, 0));}
   }
   if(playerScore==30 || playerScore==100)
      //  if(!(upgradeText->isRunning()))
      upgradeText->startTimer();
   if(upgradeText->isRunning()){
      gameScoreFont->drawText(400, 31, al_map_rgb(255,255,255), "WEAPON UPGRADED");
      if(upgradeText->getCount() > 10){
	 upgradeText->stopTimer();
	 upgradeText->resetCount();
      }

   }
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
	    if (isPointBoxCollision((*it_proj)->centre, player->centre, PLAYER_SIZE)) {	  
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
	    if (doHitboxesIntersect(player->centre, PLAYER_SIZE,
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
   if (player && doColorsMatch(player->color, c)) {
      playerScore += 1;
      playerScoreTotal += 1;
   }
}



void Single::spawn() {
   // some initializations 
   Point pt(800, 200);
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
	    addCreep(pt, al_map_rgb(255, 51, 51), spd);
	 }	 
	 break;
	 
	 
      case 2: // wave of 8
	 for (int i = 0; i < 8; i++) {
	    pt.rollRandom();
	    spd.rollRandom();
	    addCreep(pt, al_map_rgb(255, 159, 48), spd);
	 }
	 break;
   
   
      case 3: // V shaped spawn, shoots 2 shots
	 addCreep(Point(800, 300), al_map_rgb(246, 64, 234),Vector(-180, 0));
      
	 addCreep(Point(900, 350), al_map_rgb(246, 64, 234), Vector(-180, 0));
	 addCreep(Point(900, 250), al_map_rgb(246, 64, 234), Vector(-180, 0));
	 addCreep(Point(1000, 400), al_map_rgb(246, 64, 234), Vector(-180, 0));
	 addCreep(Point(1000, 200), al_map_rgb(246, 64, 234), Vector(-180, 0));
	 addCreep(Point(1100, 100), al_map_rgb(246, 64, 234), Vector(-180, 0));
	 addCreep(Point(1100, 500), al_map_rgb(246, 64, 234), Vector(-180, 0));
	 break;
      
      case 4: // 3 enemies that track to initial position of player
	 pt1.x=800; pt1.y=580;
	 pt2.x=800; pt2.y=20;
	 pt3.x=850; pt3.y=300;
	 addCreep(pt1, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt1.x)/1.5),
							((playerloc.y-pt1.y)/1.5)));
	 addCreep(pt2, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt2.x)/1.5),
							((playerloc.y-pt2.y)/1.5)));
	 addCreep(pt3, al_map_rgb(255, 255, 255),Vector(((playerloc.x-pt3.x)/1.5),
							((playerloc.y-pt3.y)/1.5)));
	 break;
      
      
      case 5:
	 pt.y=pt.y+(rand()%200);
	 addCreepB(pt, al_map_rgb(204,3,3), Vector(-60, 0));
	 //spawn();
	 break;
      
      
      case 6: 
	 color = al_map_rgb(255, 153, 255);
	 for(int i=0; i<5; i++) {
	    spd.rollReallyRandom();
	    addCreep(Point(800, 300), color, spd);
	 }
	 break;

	 //    case 7:
	 // addCreepB(Point (800, 300), al_map_rgb(204,3,3), Vector(-60, 0));
	 // break;
	 
   }
   
}


void Single::spawnBoss()
{  
   addBoss(Point(900, 300),  al_map_rgb(155, 0, 0), Vector(-100, 0));
}

void Single::addBoss(const Point& cen, const ALLEGRO_COLOR& col, const Vector& spd)
{
   enem.push_back(std::make_shared<Boss> (cen, col, spd));
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
	 
	 if((*it)->getFire()) {
	    
	    if(doColorsMatch((*it)->color, al_map_rgb(204,3,3))) {
	       CircleLaser((*it));
	    }
	    //Purple enemies will spawn two extra projectiles
	    else if(doColorsMatch((*it)->color, al_map_rgb(246, 64, 234))) {
	       addLaser((*it)->centre, (*it)->color, (*it)->getProjSpeed() + Vector(0, 40));
	       addLaser((*it)->centre, (*it)->color, (*it)->getProjSpeed() + Vector(0, -40));
	    }
	    //boss is going to spawn a lot of projectiles
	    else if(doColorsMatch((*it)->color, al_map_rgb(155, 0, 0)))
	    {
	       for(int i = -70; i <= 70; i += 20)
		  addLaser((*it)->centre, (*it)->color, (*it)->getProjSpeed() + Vector(0,i));
	    
	       /*proj.push_back(std::make_shared<Laser>((*it)->getCentre(),
		 (*it)->getColor(),
		 (*it)->getProjSpeed()+Vector(0,-10)));
		 proj.push_back(std::make_shared<Laser>((*it)->getCentre(),
		 (*it)->getColor(),
		 (*it)->getProjSpeed()+Vector(0,30)));
		 proj.push_back(std::make_shared<Laser>((*it)->getCentre(),
		 (*it)->getColor(),
		 (*it)->getProjSpeed()+Vector(0,-30)));
		 proj.push_back(std::make_shared<Laser>((*it)->getCentre(),
		 (*it)->getColor(),
		 (*it)->getProjSpeed()+Vector(0,50)));
		 proj.push_back(std::make_shared<Laser>((*it)->getCentre(),
		 (*it)->getColor(),
		 (*it)->getProjSpeed()+Vector(0,-50)));
		 proj.push_back(std::make_shared<Laser>((*it)->getCentre(),
		 (*it)->getColor(),
		 (*it)->getProjSpeed()+Vector(0,70)));
		 proj.push_back(std::make_shared<Laser>((*it)->getCentre(),
		 (*it)->getColor(),
		 (*it)->getProjSpeed()+Vector(0,-70)));
	       */
	    }
	 
	 //regular enemies spawn one straight projectile	    
	    else {
	       addLaser((*it)->centre + Vector(20, 0), (*it)->color, (*it)->getProjSpeed());
	    }
	    (*it)->setFire(false);
	 }	 	 
      }
   }
      
   if(aliveBoss == false && playerScoreTotal == 20)
   {
      spawnBoss();
      aliveBoss = true;
   }
   if(enem.size() <= 3 && aliveBoss == false) {
      spawn();
   }
}


void Single::CircleLaser(std::shared_ptr<Enemy> E)
{/*
   addLaser(E->getCentre(), E->getColor(), Vector(0, -500));   //up
   addLaser(E->getCentre(), E->getColor(), Vector(150, -350)); //UUR
   addLaser(E->getCentre(), E->getColor(), Vector(250, -250)); //UR
   addLaser(E->getCentre(), E->getColor(), Vector(500, 0));    //right
   addLaser(E->getCentre(), E->getColor(), Vector(150, 350));  //RRD
   addLaser(E->getCentre(), E->getColor(), Vector(250, 250));  //RD
   addLaser(E->getCentre(), E->getColor(), Vector(0, 500));    //down
   addLaser(E->getCentre(), E->getColor(), Vector(-2150, 250)); //DR
   addLaser(E->getCentre(), E->getColor(), Vector(-350, 150)); //DDR
   addLaser(E->getCentre(), E->getColor(), Vector(-500, 0));   //left
   addLaser(E->getCentre(), E->getColor(), Vector(-250, -250));//UL
   addLaser(E->getCentre(), E->getColor(), Vector(-150, -350));//UUL
   addLaser(E->getCentre(), E->getColor(), Vector(-350, -150));//ULL
 */
     for(int i=-500; i<=500; i+=250)
     for(int j=-500; j<=500; j+=250)
	addLaser(E->getCentre(), E->getColor(), Vector(i, j));
     E->setFire(false);
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
	 if(doColorsMatch((*it)->getColor(), al_map_rgb(204, 3, 3)))
	 {
	    (*it)->draw(enemyBomb, enemyDeath);
	 }
	 else
	 (*it)->draw(enemyShip, enemyDeath);
      }
   }
}

void Single::setupPlayer() {
   player = std::make_shared<Player> (Point(215, 245),
				      al_map_rgb(0, 200, 0));
}

void Single::cullPlayer() {
   if (player && player->dead) {
      playerLives -= 1;
      playerScore = 0;
      player.reset();
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
	 //if(doColorsMatch((*it)->getColor(), al_map_rgb(155, 0, 0)))
	 //   aliveBoss = false;
	  if (!(*it)->getdAnim_complete()) 
	     // if not dead (death animation not complete)
	     newEnem.push_back(*it);	  
      }
      enem.clear();
      enem.assign(newEnem.begin(), newEnem.end());
   }
}
