/**
 * @file Versus.cc
 * @brief Implementation of Versus class- handles game interactions for versus 
 *        mode
 *
 * @author
 * @bug
 */
#include "Background.h"
#include "Player.h"
#include "Projectile.h"
#include "Missile.h"
#include "Laser.h"
#include "Versus.h"

Versus::~Versus() {
  proj.clear();
  player1.reset();
  player2.reset();
}

void Versus::load_assets() {
  // initialize timers
  if ((gameOverTimer = al_create_timer( 1.0 / framesPerSec )) == NULL) {
    std::cerr << "Cannot initialize game over timer\n";
    exit(2);
  }
  
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


  player1 = std::make_shared<Player> (Point(200, 300),
				      al_map_rgb(255,0,0),
				      framesPerSec );

  player2 = std::make_shared<Player> (Point(600, 300),
				      al_map_rgb(0,200,0),
				      framesPerSec );	 
}

void Versus::setupBackground() {
  bg = std::make_shared<Background> (Vector(50, 0), Vector(90, 0));
}


// returns true if either player has been destroyed
bool Versus::is_game_over() {
  if (!player1 || !player2) {
    return true;
  }
  return false;
}

// MAIN UPDATE FUNCTION
void Versus::update(double dt) {
  
}

// MAIN DRAW FUNCTION
void Versus::draw() {
  bg->draw();
  //if (player1) player1->draw();
  //if (player2) player2->draw();
  if (!proj.empty())
    for (std::list< std::shared_ptr<Projectile> >::iterator it = proj.begin();
	 it != proj.end(); ++it) 
      (*it)->draw();
}

void Versus::updatePlayerAction() {

  /*
  if (!play.empty()) {
    for (std::list< std::shared_ptr<Player> >::iterator it = play.begin(); 
	 it != play.end(); ++it) {
      (*it)->updatePlayerSpeed();	 
      if ((*it)->fire) {
	proj.push_back(std::make_shared<Laser> ((*it)->centre, 
						(*it)->color,
						(*it)->projSpeed));
	(*it)->fire = false;
      }
      if ((*it)->mfire) {
	proj.push_back(std::make_shared<Missile> ((*it)->centre, 
						  (*it)->color,
						  (*it)->projSpeed));
	(*it)->mfire = false;	 	 
      }	 
    }
  }   
  */

}

void Versus::updatePlayerPosition(double dt) {
  if (player1) player1->update(dt);
  if (player2) player2->update(dt);
  /*
  if (!play.empty()) {
    for (std::list< std::shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
      (*it)->update(dt);
    }
  }   
  */
}

void Versus::updateProjectilePosition(double dt) {
  if (!proj.empty()) {
    for (std::list< std::shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) {
      (*it)->update(dt);
    }
  }
}

// simple square-bound box collision detection
void Versus::collision() {

  /*
  if (!proj.empty()) {
    // projectiles exist
    for (std::list< std::shared_ptr<Projectile> >::iterator i = proj.begin(); i != proj.end(); ++i) {
      // check against players
      if (!play.empty()) {
	for (std::list< std::shared_ptr<Player> >::iterator p = play.begin(); p != play.end(); ++p) {
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
    }*/
}

void Versus::clean() {
  cullPlayers();
  cullProjectiles();
}


void Versus::cullPlayers() {
  if (player1)
    if (player1->dead)
      player1.reset();
  if (player2)
    if (player2->dead)
      player2.reset();

  /*
  std::list< std::shared_ptr<Player> > newPlay;
  if (!play.empty()) {
    for (std::list< std::shared_ptr<Player> >::iterator it = play.begin(); it != play.end(); ++it) {
      if (!(*it)->dead) // if not dead
	newPlay.push_back(*it);
    }
    play.clear();
    play.assign(newPlay.begin(), newPlay.end());      
    }*/
}

void Versus::cullProjectiles() {
  std::list< std::shared_ptr<Projectile> > newProj;
  if (!proj.empty()) {
    for (std::list< std::shared_ptr<Projectile> >::iterator it = proj.begin(); it != proj.end(); ++it) {
      if ((*it)->live) // if live
	newProj.push_back(*it);
    }
    proj.clear();
    proj.assign(newProj.begin(), newProj.end());      
  }
}

void Versus::updateScore(ALLEGRO_COLOR& c) {
  if (player1) {
    ALLEGRO_COLOR tmp = player1->color;
    if (tmp.r == c.r && tmp.g == c.g && tmp.b == c.b) {
      player1->score += 1;
    }    
  }
  if (player2) {
    ALLEGRO_COLOR tmp = player2->color;
    if (tmp.r == c.r && tmp.g == c.g && tmp.b == c.b) {
      player2->score += 1;
    }    
  }
}

void Versus::input(ALLEGRO_EVENT& inputEvent) {
  /*
  if (player1) {
    player1->input(inputEvent);
  }
  if (player2) {
    player2->input(inputEvent);
    }*/
}
