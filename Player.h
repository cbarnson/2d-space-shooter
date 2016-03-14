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
//const int arraySize;
   
   ALLEGRO_TIMER *fireDelay = NULL;
   ALLEGRO_BITMAP *ship = NULL;
   //ALLEGRO_BITMAP *ship[arraySize];  
   //ALLEGRO_BITMAP *shipImage;
   ALLEGRO_FONT *scoreFont = al_load_font("/usr/share/fonts/dejavu/DejaVuSerif.ttf", 18, 0);

   //sprite stuff
   int shipWidth;
   int shipHeight;

   bool dead;           // signals Player object has been killed
   bool fire;           // true if fire-key has been hit
   Vector projSpeed;    // speed of projectiles
   int lives;           // lives remaining before destroyed
   int speed_modifier;
   int size;            // ship size in pixels
   int score;

   //variables needed for the animation of the sprite
   int maxFrame = 3; //dont want to cycle through all of the frames
   int currFrame = 3; //
   int frameCount = 0;
   int frameDelay = 50; //not using
   int frameHeight = 40; //
   int frameWidth = 46; //
   int animCol = 0;
   int animRow = 1;
   int animDirection = 1;
      
  public:

  Player(Point p, ALLEGRO_COLOR c, vector<int> h, bool f, int frames)
     : centre(p), color(c), config(h), flipped(f), fps(frames)
   {      
      if ((fireDelay = al_create_timer(1.0 / fps)) == NULL)
	 throw std::runtime_error("Cannot create fireDelay timer");
      al_start_timer(fireDelay);

      //These are the things for the sprite
      scoreFont = al_load_font("/usr/share/fonts/dejavu/DejaVuSerif.ttf", 18, 0);

      ship = al_load_bitmap("/home/meyd2720/project/sprites/Sprite2.png");
      //shipImage = al_load_bitmap("/home/meyd2720/project/sprites/Sprite.png");
      
      if (ship == NULL)
	 std::cout << "image was not loaded\n";
      
      shipWidth = al_get_bitmap_width(ship);
      shipHeight = al_get_bitmap_height(ship);
      
      speed = Vector(0,0);
      lives = 1;
      size = 10;
      score = 0;
      
      dead = false;
      fire = false;
      speed_modifier = 300;
      projSpeed = (flipped) ? Vector(-200,0) : Vector(200,0);
   }

   ~Player() {
      if (fireDelay != NULL)
	 al_destroy_timer(fireDelay);
      //al_destroy_bitmap(shipImage);
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

   //void resetAnimation();
};

#endif
