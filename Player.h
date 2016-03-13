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

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <iostream>
#include <stdexcept>

using std::shared_ptr;
using std::make_shared;
using std::vector;

class Player : public Controls, public Drawable, public Updateable {
  private:
   Point centre;        // ship position
   ALLEGRO_COLOR color; // ship color
   Vector speed;        // movement speed in any direction
   Hotkeys config;      // key mapping profile
   bool flipped;
   int fps;

   ALLEGRO_TIMER *fireDelay = NULL;
   //ALLEGRO_BITMAP *ship = NULL;
   ALLEGRO_FONT *scoreFont = al_load_font("/usr/share/fonts/dejavu/DejaVuSerif.ttf", 18, 0);

   //int shipWidth;
   //int shipHeight;

   bool dead;           // signals Player object has been killed
   bool fire;           // true if fire-key has been hit
   Vector projSpeed;    // speed of projectiles
   int lives;           // lives remaining before destroyed
   int speed_modifier;
   int size;            // ship size in pixels
   int score;
   
  public:

  Player(Point p, ALLEGRO_COLOR c, vector<int> h, bool f, int frames)
     : centre(p), color(c), config(h), flipped(f), fps(frames)
   {      
      if ((fireDelay = al_create_timer(1.0 / fps)) == NULL)
	 throw std::runtime_error("Cannot create fireDelay timer");
      al_start_timer(fireDelay);
      
      //scoreFont = al_load_font("/usr/share/fonts/dejavu/DejaVuSerif.ttf", 18, 0);
      //ship = al_load_bitmap("/home/barc2720/assn/al2/goodFighter.png");
      //if (ship == NULL)
      // std::cout << "image was not loaded\n";
      //shipWidth = al_get_bitmap_width(ship);
      //shipHeight = al_get_bitmap_height(ship);
      
      speed = Vector(0,0);
      lives = 1;
      size = 10;
      score = 0;
      
      dead = false;
      fire = false;
      speed_modifier = 200;
      projSpeed = (flipped) ? Vector(-400,0) : Vector(400,0);
   }

   ~Player() {
      if (fireDelay != NULL)
	 al_destroy_timer(fireDelay);
   }

   // set methods
   void setLives(int);
   void setFire(bool);
   void hit();

   // get methods
   int getLives();
   int getSize();
   bool getDead();
   bool getFire();
   Point getCentre();
   Vector getSpeed();
   ALLEGRO_COLOR getColor();
   
   void set(int);
   void reset(int);
   void draw();
   void updatePlayer();
   void update(double);      
   
};

#endif
