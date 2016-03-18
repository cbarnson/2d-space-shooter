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

class Player : public Controls, public Drawable, public Updateable {
  private:
   Point centre;        // ship position
   ALLEGRO_COLOR color; // ship color
   Vector speed;        // movement speed in any direction
   Hotkeys config;      // key mapping profile
<<<<<<< HEAD
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
=======
   bool flipped;        // for 'versus' mode
   int fps;             // for our timer

   ALLEGRO_TIMER *fireDelay;
   ALLEGRO_FONT *scoreFont;
>>>>>>> bce9dd668c6fa32b872f3c8ae3f237ff53541e1a

   Sprite *ship;
   
   bool dead;           // signals Player object has been killed
   bool fire;           // signals fire-key has been hit
   Vector projSpeed;    // speed of projectiles from Player object
   int lives;           // lives remaining of Player object before destroyed
   int speed_modifier;  // affects speed of Player object
   int size;            // ship size in pixels
<<<<<<< HEAD
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
      
=======
   int score;           // score of Player object
   int row;
   int col;
   

>>>>>>> bce9dd668c6fa32b872f3c8ae3f237ff53541e1a
  public:

  Player(Point p, ALLEGRO_COLOR c, vector<int> h, bool f, int frames)
     : centre(p), color(c), config(h), flipped(f), fps(frames)
   {      
      if ((fireDelay = al_create_timer(1.0 / fps)) == NULL)
	 throw std::runtime_error("Cannot create fireDelay timer");
      al_start_timer(fireDelay);

<<<<<<< HEAD
      //These are the things for the sprite
      scoreFont = al_load_font("/usr/share/fonts/dejavu/DejaVuSerif.ttf", 18, 0);

      ship = al_load_bitmap("/home/meyd2720/project/sprites/Sprite2.png");
      //shipImage = al_load_bitmap("/home/meyd2720/project/sprites/Sprite.png");
      
      if (ship == NULL)
	 std::cout << "image was not loaded\n";
      
      shipWidth = al_get_bitmap_width(ship);
      shipHeight = al_get_bitmap_height(ship);
      
=======
      //cout << "pre player load assets\n";
      load_assets();
      
      projSpeed = (flipped) ? Vector(-400,0) : Vector(400,0);
      speed_modifier = 200;
>>>>>>> bce9dd668c6fa32b872f3c8ae3f237ff53541e1a
      speed = Vector(0,0);
      lives = 3;
      size = 10;
      score = 0;
      row = 0;
      col = 0;
      
      dead = false;
      fire = false;
   }

<<<<<<< HEAD
   ~Player() {
      if (fireDelay != NULL)
	 al_destroy_timer(fireDelay);
      //al_destroy_bitmap(shipImage);
   }
=======
   ~Player();
>>>>>>> bce9dd668c6fa32b872f3c8ae3f237ff53541e1a

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

   void load_assets();
   void hit();   
   void set(int);
   void reset(int);
   void draw();
   void updatePlayer();
<<<<<<< HEAD
   void update(double);

   //void resetAnimation();
=======
   void update(double);      
   
>>>>>>> bce9dd668c6fa32b872f3c8ae3f237ff53541e1a
};

#endif
