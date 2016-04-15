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
#include <fstream>

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
#include "CreepMis.h"
#include "CreepBomb.h"
#include "Boss.h"

const int GAME_OVER_WAIT_TIME = 100;
const int HIGH_SCORE_DISPLAY_TIME = 200;
const int WEAPON_DELAY_LASER = 6;
const int WEAPON_DELAY_MISSILE = 20;
const Vector PLAYER_PROJECTILE_SPEED = Vector(500, 0);

//-------------------------------
// CONSTRUCTOR
//-------------------------------
Single::Single(int w, int h, int f, std::string playerName) :
   Root(w, h, f),
   _playerName(playerName),
   gameOver(false),
   playerLives(3),
   playerScoreTotal(0),
   playerScore(0)
{
   
}

//------------------------------
// DESTRUCTOR
//-------------------------------
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

   al_destroy_font(_font24);
}

//---------------------------------
// INIT MAIN
//---------------------------------
void Single::init() {
   // timers
   gameOverTimer = std::make_shared<Timer> (framesPerSec); gameOverTimer->create();
   playerWeapon1 = std::make_shared<Timer> (framesPerSec); playerWeapon1->create();   
   playerWeapon2 = std::make_shared<Timer> (framesPerSec); playerWeapon2->create();
   playerRespawn = std::make_shared<Timer> (framesPerSec); playerRespawn->create();
   bossTimer     = std::make_shared<Timer> (framesPerSec); bossTimer->create();
   upgradeText   = std::make_shared<Timer> (framesPerSec); upgradeText->create();
   playerWeapon1->startTimer();
   playerWeapon2->startTimer();
   // create Player object
   setupPlayer();
   // go to resources directory
   ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
   al_append_path_component(path, "resources");
   al_change_directory(al_path_cstr(path, '/'));   
   // fonts
   _font24 = al_load_font("ipag.ttf", 24, 0);
   gameOverFont = std::make_shared<Font> ("DavidCLM-BoldItalic.ttf", 64); gameOverFont->load();
   gameScoreFont = std::make_shared<Font> ("ipag.ttf", 18); gameScoreFont->load();   
   // background
   bg = std::make_shared<Background> (Vector(50, 0), Vector(-90, 0));
   // sprites
   playerShip = std::make_shared<Sprite> ("Sprite2.png");
   enemyShip = std::make_shared<Sprite> ("EnemyBasic.png");
   enemyDeath = std::make_shared<Sprite> ("explode.png");
   enemyBomb  = std::make_shared<Sprite> ("spikebomb.png");
   bossShip   = std::make_shared<Sprite> ("bossv2.png");
   // delete path 
   al_destroy_path(path);
}

//------------------------------
// UPDATE MAIN
//-----------------------------
void Single::update(double dt) {
   // background
   bg->update(dt);
   // player
   if (player) {
      player->update(dt);
   }
   // gameover condition
   else if (!player && playerLives <= 0) {
      gameOver = true;
   }
   // respawn condition
   else {
      respawnPlayer();
   }

   // do boss stuff here
   updateBoss();
   
   // projectiles
   updateProjectilePosition(dt);
   // enemies
   updateEnemyPosition(dt);
   // all collision
   collision();
   // cull enities out of bound or dead
   clean();      
}
//------------------------------
// DRAW MAIN
//-----------------------------
// renders the entire scene
void Single::draw() {
   // background
   bg->draw();
   // life indicator
   drawLives();
   // projectiles on screen
   drawProjectiles();
   // enemies on screen
   drawEnemies(); 
   // conditional boss message
   drawBossIncomingMessage();
   
   if (gameOver) {
      showGameOverMessage();
   }
   else if (player) {
      player->draw(playerShip, 0);
   }
   gameScoreFont->drawTextF(al_map_rgb(255, 255, 255), 100, 50,"Score: %i", playerScoreTotal);
   drawWeaponUpgradeStatus();
   //bossIntro();
}

//--------------------------------
// INPUT MAIN
//--------------------------------
void Single::input(ALLEGRO_KEYBOARD_STATE& kb) {
   if (player) {
      switch (player->input(kb)) { // movement events are handled within player	 
	 case act::action::QUIT_GAME: 
	    player.reset();
	    return;
	    
	 case act::action::FIRE_PRIMARY: // case to handle lasers	    
	    // single
	    if (playerWeapon1->getCount() > WEAPON_DELAY_LASER && playerScore < 30) {
	       addPlayerLaserSingleShot();
	    }	    
	    // double
	    else if (playerWeapon1->getCount() > WEAPON_DELAY_LASER + 4 &&
		playerScore >= 30 && playerScore < 100) {
	       addPlayerLaserDoubleShot();
	    }	    
	    // triple
	    else if (playerWeapon1->getCount() > WEAPON_DELAY_LASER + 6 &&
		playerScore >= 100) {
	       addPlayerLaserTripleShot();
	    }
	    break;
	    
	 case act::action::FIRE_SECONDARY: // case to handle missile
	    // single
	    if (playerWeapon2->getCount() > WEAPON_DELAY_MISSILE) {
	       addPlayerMissileSingleShot();
	    }
	    break;
	    
	 default:
	    break;
      }
   }
}



// returns true if the gameOver is true and if the game over screen has completed
// its duration
bool Single::is_game_over() {
   // change this condition------------
   if (gameOver && gameOverTimer->getCount() > GAME_OVER_WAIT_TIME + HIGH_SCORE_DISPLAY_TIME) {
      // flush the display
      bg->draw();
      return true;
   }
   return false;
}


void Single::spawn() {
   // some initializations 
   Point pt(800, 200);
   Point pt1, pt2, playerloc, pt3;
   Vector spd(0, 0);
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
	 spd.Angle(playerloc, pt1, 1);
	 addCreep(pt1, al_map_rgb(255, 255, 255),spd);
	 spd.Angle(playerloc, pt2, 1);
	 addCreep(pt2, al_map_rgb(255, 255, 255),spd);
	 spd.Angle(playerloc, pt3, 1);
	 addCreep(pt3, al_map_rgb(255, 255, 255),spd);
	 break;
            
      case 5:
	 pt.y=pt.y+(rand()%200);
	 addCreepB(pt, al_map_rgb(204,3,3), Vector(-60, 0));
	 break;
	 
      case 6:
	 for(int i = 800; i <= 1000; i += 50) {
	    addCreepMis(Point(i,300), Point(700,100), Point(100,100),
			Point(100,500), Point(700,500), al_map_rgb(255,254,253),
			Vector(-90, 0));
	 }
	 break;
      default:
	 break;
   }   
}




void Single::CircleLaser(std::shared_ptr<Enemy> E) {
   
   for(int i = -500; i <= 500; i += 325) {
      for(int j = -500; j <= 500; j += 325) {
	 addLaser(E->getCentre(), E->getColor(), Vector(i, j));
      }
   }
   /* addLaser(E->getCentre(), E->getColor(), Vector(500 , 0 ));
   addLaser(E->getCentre(), E->getColor(), Vector(0 ,500 ));
   addLaser(E->getCentre(), E->getColor(), Vector(-500 ,0 ));
   addLaser(E->getCentre(), E->getColor(), Vector(0 ,-500 ));
   addLaser(E->getCentre(), E->getColor(), Vector(250 , 250 ));
   addLaser(E->getCentre(), E->getColor(), Vector(250 ,-250 ));
   addLaser(E->getCentre(), E->getColor(), Vector(-250 ,250 ));
   addLaser(E->getCentre(), E->getColor(), Vector(-250 ,-250 ));
   addLaser(E->getCentre(), E->getColor(), Vector(350 , 150 ));
   addLaser(E->getCentre(), E->getColor(), Vector(150 ,350 ));
   addLaser(E->getCentre(), E->getColor(), Vector(-350 ,150 ));
   addLaser(E->getCentre(), E->getColor(), Vector(350 ,-150 ));
   addLaser(E->getCentre(), E->getColor(), Vector(-150 ,350 ));*/
   E->setFire(false);

}
void Single::bossFire(std::shared_ptr<Enemy> e){
   //if (!bossFirstShot) {
   //      for(int i = 800; i <= 1000; i += 50) {
   //	 addCreepMis(Point(i,300), Point(750,50), Point(580,50),
   //		     Point(580,550), Point(750,550), al_map_rgb(255,254,253), Vector(-90, 0));
      //}
      // bossFirstShot = true;
      //}
   int n = rand() % 7 + 1;
   Point playerloc;
if (player) {
      playerloc = player->centre;
   }
   Vector aim(0, 0);
   //change this to be based on lives
   switch(n) {
      case 1:
	 for(int i=-100; i<=100; i+=20)
	    addLaser(e->centre+Point(0, i), e->color, e->getProjSpeed());
	 break;
      case 2:
	 aim.Angle(playerloc, e->centre, 0.9);
	 for(int i = -70; i <= 70; i += 20)
	    addLaser(e->centre+Point(50,0), e->color, aim+ Vector(-30,i));
	break;
      case 3:
	 addCreepB(e->centre+Point(50,0), al_map_rgb(204,3,3), Vector(-100, 0));
	 break;
      default:
	 aim.Angle(playerloc, e->centre+Point(0,50), 0.9);
	 addMissile(e->centre+Point(0,50), al_map_rgb(204, 3, 3), aim);
	 aim.Angle(playerloc, e->centre+Point(0,-50), 0.9);
	 addMissile(e->centre+Point(0,-50), al_map_rgb(204, 3, 3), aim);
	 break;
   }
}
   



//==================================
// UPDATE FUNCTIONS
//=================================
void Single::spawnBoss() {
   addBoss(Point(850, 300), al_map_rgb(155, 0, 0), Vector(-50, 0));
   bossExists = true;

}

void Single::addBoss(const Point& cen, const ALLEGRO_COLOR& col, const Vector& spd) {
   enem.push_back(std::make_shared<Boss> (cen, col, spd));
}

void Single::updateBoss() {
   // spawn condition
   if (bossSpawnConditionCounter > 30 && bossExists == false) {
      // start timer
      if (bossTimer->isRunning() == false) {
	 bossTimer->startTimer();
	 bossIncoming = true;
      }
      if (bossTimer->getCount() > 250) {
	 spawnBoss(); // bossExists set to true from here
	 bossTimer->stopTimer();
	 bossTimer->resetCount();
	 bossIncoming = false;
      }      
   }
}

void Single::drawBossIncomingMessage() {
   if (bossTimer->isRunning() == true && bossIncoming == true) {
      gameOverFont->drawTextCentered(al_map_rgb(204, 204, 0), "BOSS INCOMING");
      if (bossTimer->getCount() > 200) {
	 bossIncoming = false;
      }      
   }
}

void Single::updateHighscores() {
   if (writeComplete == false) { // make sure this is a one time event
      _highscores = std::make_shared<Score> ("leaderboard.txt");
      _highscores->init();
      _highscores->readPrev();
      if (_highscores->getMin() < playerScoreTotal) {
	 _highscores->swapWithMin(_playerName, playerScoreTotal);
	 _highscores->sortRecords();
      }
      _highscores->update();
      writeComplete = true;
   }
}

void Single::updateScore(ALLEGRO_COLOR& c) {
   if (player && doColorsMatch(player->color, c)) {
      playerScore += 1;
      playerScoreTotal += 1;
      bossSpawnConditionCounter+=1;
   }
}

void Single::updateProjectilePosition(double dt) {
   if (!proj.empty()) {
      for (auto it = proj.begin(); it != proj.end(); ++it) {
	 (*it)->update(dt);
      }
   }
}

void Single::updateEnemyPosition(double dt) {
   if (!enem.empty()) {
      for (auto it = enem.begin(); it != enem.end(); ++it) {
	 (*it)->update(dt);
	 //fire routines for regular enemies	 
	 if ((*it)->getFire()) {
	    //explosion of lasers from creepBomb	    
	    if (doColorsMatch((*it)->color, al_map_rgb(204,3,3))) {
	       CircleLaser((*it));
	    }
	    //boss fire mechanics
	    if (doColorsMatch((*it)->color, al_map_rgb(155, 0, 0))) {
	       bossFire((*it));
	    }	    
	    //Purple enemies will spawn two extra projectiles
	    else if (doColorsMatch((*it)->color, al_map_rgb(246, 64, 234))) {
	       addLaser((*it)->centre, (*it)->color, (*it)->getProjSpeed() + Vector(0, 40));
	       addLaser((*it)->centre, (*it)->color, (*it)->getProjSpeed() + Vector(0, -40));
	    }	    
	    else { //regular fire- straight horizontal shot
	       addLaser((*it)->centre + Vector(20, 0), (*it)->color, (*it)->getProjSpeed());
	    }
	    (*it)->setFire(false);
	 }
      }
   }

   if (enem.size() <= 3 && bossExists == false && !bossIncoming) {
      spawn();
   }
}

void Single::collision() {
   checkCollisionOnPlayer();
   checkCollisionOnEnemies();
   checkCollidingEnemyWithPlayer();
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
		  if ((*it_enem)->getDead()) {
		     updateScore(player->color);
		  }
	       }
	    }
	 }
      }
   }
}

void Single::checkCollidingEnemyWithPlayer() {
   if (!enem.empty() && player) {      
      for (auto it = enem.begin(); it != enem.end(); ++it) {	 
	 if ((*it)->dead == false) {	    
	    if (doHitboxesIntersect(player->centre, PLAYER_SIZE, (*it)->centre, 
				    (*it)->getSize())) {
	       // collision - register damage
	       (*it)->hit();
	       player->hit(1);
	    }
	 }	       
      }
   }  
}


void Single::checkCollisionOnPlayer() {
   if (!proj.empty() && player) {
      for (auto it = proj.begin(); it != proj.end(); ++it) {	    
	 // check if projectile color is different from player color
	 if (!doColorsMatch((*it)->color, player->color)) {
	    if (isPointBoxCollision((*it)->centre, player->centre, PLAYER_SIZE)) {	  
	       // register damage on player and flag projectile as dead
	       (*it)->live = false;
	       player->hit(1);
	    }
	 }
      }
   }  
}

void Single::clean() {
   cullPlayer();
   cullProjectiles();
   cullEnemies();
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
      for (auto it = enem.begin(); it != enem.end(); ++it) {
	 // color check for boss
	 if (doColorsMatch((*it)->getColor(), al_map_rgb(155, 0, 0))) {
	    if ((*it)->getdAnim_complete()) {
	       if(playerLives<3)
		  playerLives++;
	       bossExists = false;
	       bossFirstShot = false;
	       bossSpawnConditionCounter=0;
	    }
	 }
	 if (!(*it)->getdAnim_complete()) {
	     // if not dead (death animation not complete)
	    newEnem.push_back(*it);
	 }
      }
      enem.clear();
      enem.assign(newEnem.begin(), newEnem.end());
   }
}



void Single::respawnPlayer() {
   if (!playerRespawn->isRunning()) {
      playerRespawn->startTimer();
   }
   if (playerRespawn->getCount() > 80) {
      setupPlayer();
      playerRespawn->stopTimer();
      playerRespawn->resetCount();
   }
}



//==================================
// DRAW FUNCTIONS
//=================================
void Single::drawProjectiles() {
   if (!proj.empty()) {
      for (auto it = proj.begin(); it != proj.end(); ++it) { 
	 (*it)->draw();
      }
   }
}

void Single::drawEnemies() {
   if (!enem.empty()) {
      for (auto it = enem.begin(); it != enem.end(); ++it) {
	 if (doColorsMatch((*it)->getColor(), al_map_rgb(204, 3, 3))) {
	    // bomb enemy
	    (*it)->draw(enemyBomb, enemyDeath);
	 }
	 else if (doColorsMatch((*it)->getColor(), al_map_rgb(155, 0, 0))) {
	    // boss enemy
	    (*it)->draw(bossShip, enemyDeath);
	 }				
	 else {
	    // creep enemy
	    (*it)->draw(enemyShip, enemyDeath);
	 }
      }
   }
}

void Single::drawLives() {
   Point centre(displayWidth-70, displayWidth-50);
   if (playerLives > 0) {
	  al_draw_rectangle(displayWidth - 70, 50, displayWidth - 50, 70,
			    al_map_rgb(0, 255, 0), 5);
   }
   if (playerLives > 1) {
      al_draw_rectangle(displayWidth - 110, 50, displayWidth - 90, 70,
			al_map_rgb(0, 255, 0), 5);
   }
   if (playerLives > 2) {
      al_draw_rectangle(displayWidth - 150, 50, displayWidth - 130, 70,
			al_map_rgb(0, 255, 0) , 5);
   }   
   if (!player && playerLives > 0) {
      gameOverFont->drawTextCenteredF(al_map_rgb(255, 0, 0), "%i LIVES REMAINING", playerLives);
   }
}

void Single::drawWeaponUpgradeStatus() {   
   al_draw_rounded_rectangle(displayWidth - (displayWidth / 2) - 50, 50,
			     displayWidth - (displayWidth / 2) + 50,
			     70, 2, 2, al_map_rgb(255, 255, 255), 1);
   if (playerScore != 0) {
      
      if (playerScore < 30) {
	 al_draw_filled_rounded_rectangle(displayWidth - (displayWidth / 2) - 49, 51,
					  displayWidth - (displayWidth / 2) - 49 +
					  playerScore * 3.3, 69, 2, 2,
					  al_map_rgb(255, 0, 0));
      }
      if (playerScore >= 30 && playerScore < 100) {
	 al_draw_filled_rounded_rectangle(displayWidth - (displayWidth / 2) - 49, 51,
					  displayWidth - (displayWidth / 2) - 49 +
					  (playerScore - 30) * 1.428, 69, 2, 2,
					  al_map_rgb(255, 0, 0));
      }
      if (playerScore >= 100){
	 al_draw_filled_rounded_rectangle(displayWidth - (displayWidth / 2) - 49, 51,
					  displayWidth - (displayWidth / 2) + 49, 69,
					  2, 2, al_map_rgb(0, 255, 0));
      }
   }
   if (playerScore == 30 || playerScore == 100) {
      upgradeText->startTimer();
   }
   if (upgradeText->isRunning()) {
      gameScoreFont->drawText(400, 31, al_map_rgb(255,255,255), "WEAPON UPGRADED");
      
      if (upgradeText->getCount() > 50) {
	 upgradeText->stopTimer();
	 upgradeText->resetCount();
      }
   }
}

void Single::showGameOverMessage() {
   if (!gameOverTimer->isRunning()) {
      // start timer and update scores
      gameOverTimer->startTimer();
      updateHighscores();
   }
   if (gameOverTimer->getCount() < GAME_OVER_WAIT_TIME) {
      // game over message
      gameOverFont->drawTextCentered(al_map_rgb(255, 0, 0), "GAME OVER");
   }   
   else {
      // draw high scores
      drawHighScores();
   }
}

// draw each of the 3 lines with x = 300
// then y = 150, 300, 450
void Single::drawHighScores() {
   int yPosition = 150;
   for (int i = 0; i < 3; i++) {
      
      al_draw_textf(_font24,                    // font
		    al_map_rgb(255, 255, 255),  // color
		    300,                        // x
		    yPosition,                  // y
		    0,                          // flags
		    "%i. %s %i", i + 1,             
		    _highscores->getName(i).c_str(),
		    _highscores->getScore(i));
      yPosition += 150;
   }
}


//==================================
// ADD FUNCTIONS FOR GAME COMPONENTS
//=================================

void Single::setupPlayer() {
   player = std::make_shared<Player> (Point(215, 245), al_map_rgb(0, 200, 0));
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


void Single::addCreepMis(const Point& cen, Point p1, Point p2, Point p3, Point p4,
			 const ALLEGRO_COLOR& col, const Vector& spd) {
   enem.push_back(std::make_shared<CreepMis>(cen, p1, p2, p3, p4, col, spd));
}


void Single::addPlayerLaserSingleShot() {
   addLaser(player->centre + Point(-20, 0), player->color, PLAYER_PROJECTILE_SPEED);
   playerWeapon1->srsTimer();
}
void Single::addPlayerLaserDoubleShot() {
   addLaser(player->centre + Point(-25, 10), player->color,
	    PLAYER_PROJECTILE_SPEED);
   addLaser(player->centre + Point(-25, -10), player->color,
	    PLAYER_PROJECTILE_SPEED);
   playerWeapon1->srsTimer();
}
void Single::addPlayerLaserTripleShot() {
   addLaser(player->centre, player->color, PLAYER_PROJECTILE_SPEED);
   addLaser(player->centre + Point(0, 5), player->color,
	    Vector(0, 75) + PLAYER_PROJECTILE_SPEED);
   addLaser(player->centre + Point(0, -5), player->color,
	    Vector(0, -75) + PLAYER_PROJECTILE_SPEED);
   playerWeapon1->srsTimer();
}
void Single::addPlayerMissileSingleShot() {
   addMissile(player->centre, player->color, PLAYER_PROJECTILE_SPEED);
   playerWeapon2->srsTimer();
}

//==================================
// UTILITY FUNCTIONS
//=================================

// where p1 is the point, p2 is the centre of the 'box' object, with half of 
// its width s2
bool Single::isPointBoxCollision(const Point& p1, const Point& p2, 
				 const int& s2) {
   return ((p1.x > p2.x - s2) &&
	   (p1.x < p2.x + s2) &&
	   (p1.y > p2.y - s2) &&
	   (p1.y < p2.y + s2));
}


bool Single::doColorsMatch(const ALLEGRO_COLOR& a, const ALLEGRO_COLOR& b) {
   return (a.r == b.r && a.g == b.g && a.b == b.b);
}


bool Single::doHitboxesIntersect(const Point& centre1, const int& size1,
				 const Point& centre2, const int& size2) {
   return (abs(centre1.x - centre2.x) < (size1 + size2) &&
	   abs(centre1.y - centre2.y) < (size1 + size2));
}

