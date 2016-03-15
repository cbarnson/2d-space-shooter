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
   bool flipped;        // for 'versus' mode
   int fps;             // for our timer

   ALLEGRO_TIMER *fireDelay;
   
   //ALLEGRO_PATH *path;
   //ALLEGRO_FONT *scoreFont;

   /*
   ALLEGRO_BITMAP *ship00;   
   ALLEGRO_BITMAP *ship01;
   ALLEGRO_BITMAP *ship10;
   ALLEGRO_BITMAP *ship11;
   ALLEGRO_BITMAP *ship20;
   ALLEGRO_BITMAP *ship21;
   ALLEGRO_BITMAP *curAnim;
   */
   
   bool dead;           // signals Player object has been killed
   bool fire;           // signals fire-key has been hit
   Vector projSpeed;    // speed of projectiles from Player object
   int lives;           // lives remaining of Player object before destroyed
   int speed_modifier;  // affects speed of Player object
   int size;            // ship size in pixels
   int score;           // score of Player object

   
  public:

  Player(Point p, ALLEGRO_COLOR c, vector<int> h, bool f, int frames)
     : centre(p), color(c), config(h), flipped(f), fps(frames)
   {      
      if ((fireDelay = al_create_timer(1.0 / fps)) == NULL)
	 throw std::runtime_error("Cannot create fireDelay timer");
      al_start_timer(fireDelay);
      
      //ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      //al_append_path_component(path, "resources");
      //al_change_directory(al_path_cstr(path, '/'));
      /*
      ship00 = al_load_bitmap("ship00.png");      
      ship01 = al_load_bitmap("ship01.png");
      ship10 = al_load_bitmap("ship10.png");
      ship11 = al_load_bitmap("ship11.png");
      ship20 = al_load_bitmap("ship20.png");
      ship21 = al_load_bitmap("ship21.png");
      */
      //scoreFont = al_load_font("ipag.tff", 16, 0);
      //al_destroy_path(path);
            
      speed = Vector(0,0);
      lives = 3;
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
      /*
      al_destroy_bitmap(ship00);
      al_destroy_bitmap(ship01);
      al_destroy_bitmap(ship10);
      al_destroy_bitmap(ship11);
      al_destroy_bitmap(ship20);
      al_destroy_bitmap(ship21);
      */
      //al_destroy_font(scoreFont);
   }

   // set methods
   void setLives(int);
   void setScore(int); // increments score by param value
   void setFire(bool);

   // get methods
   int getLives();
   int getSize();
   bool getDead();
   bool getFire();
   Point getCentre();
   Vector getProjSpeed();
   Vector getSpeed();
   ALLEGRO_COLOR getColor();

   void hit();   
   void set(int);
   void reset(int);
   void draw();
   void updatePlayer();
   void update(double);      
   
};

#endif
