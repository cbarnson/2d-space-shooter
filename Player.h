/**
 * @file Player.h
 * @brief class definition of the Player class
 *
 * This class inherits public members of Controls and Drawable
 *
 * @author
 * @bug
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Point.h"
#include "Vector.h"
#include "Updateable.h"
#include "Drawable.h"
#include "Controls.h"
#include "Hotkeys.h"
#include "Sprite.h"
#include "Projectile.h"
#include "Laser.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::vector;

class Player : public Drawable, public Updateable {
  public:

  Player(Point p, ALLEGRO_COLOR c, vector<int> h, bool f, int frames)
     : centre(p), color(c), config(h), flipped(f), fps(frames)
   {      
      load_assets();      
   }

   ~Player();

   // set methods
   void setLives(int);
   void setScore(int); // increments score by param value
   void setFire(bool); 
   void setmFire(bool);

   // get methods
   int getLives();
   int getSize();
   bool getDead();
   bool getFire();
   bool getmFire();
   Point getCentre();
   Vector getProjSpeed();
   Vector getSpeed();
   ALLEGRO_COLOR getColor();

   void hit(int);

   void input(const ALLEGRO_EVENT&);
   void updatePlayerSpeed();
   void draw();
   void update(double);

   
  private:
   Point centre;        // ship position
   ALLEGRO_COLOR color; // ship color
   Vector speed;        // movement speed in any direction
   Hotkeys config;      // key mapping profile
   bool flipped;        // for 'versus' mode
   int fps;             // for our timer

   ALLEGRO_TIMER *fireDelay;
   ALLEGRO_TIMER *missileDelay;
   ALLEGRO_FONT *scoreFont;
   shared_ptr<Sprite> ship;
   
   bool dead;           // signals Player object has been killed
   bool fire;           // signals fire-key has been hit
   bool mfire;
   Vector projSpeed;    // speed of projectiles from Player object
   int lives;           // lives remaining of Player object before destroyed
   int speed_modifier;  // affects speed of Player object
   int size;            // ship size in pixels
   int score;           // score of Player object
   int row;
   int col;

   // HELPER FUNCTIONS - simplicity and readability
   void load_assets();
   void selectShipAnimation();
   void firePrimaryWeapon();
   void fireSecondaryWeapon();
   void checkBoundary();
   void drawRemainingLife();
   void handleKeyDown(const ALLEGRO_EVENT&);
   void handleKeyUp(const ALLEGRO_EVENT&);


   
};

#endif
