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

#include "Updateable.h"
#include "Drawable.h"
#include "Projectile.h"
#include "Laser.h"
#include "Action.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <vector>

struct Point;
struct Vector;
class Sprite;
class Input;

class Player : public Updateable {
  public:
   Point centre;        // ship position
   ALLEGRO_COLOR color; // ship color
   Vector speed;        // movement speed in any direction
   //bool flipped;        // for 'versus' mode
   int fps;             // for our timer

   Input* playerInput;

   bool dead;           // signals Player object has been killed
   Vector projSpeed;    // speed of projectiles from Player object
   int lives;           // lives remaining of Player object before destroyed
   int speed_modifier;  // affects speed of Player object
   int size;            // ship size in pixels
   int score;           // score of Player object
   int row;
   int col;
   
   Player(Point p, ALLEGRO_COLOR c, int frames);

   ~Player();

   void hit(int);
   act::action input(ALLEGRO_KEYBOARD_STATE&);
   void draw(std::shared_ptr<Sprite>);
   void update(double);

   
  private:
   ALLEGRO_FONT *scoreFont;


   // HELPER FUNCTIONS - simplicity and readability
   void load_assets();
   void selectShipAnimation();
   void checkBoundary();
   void drawRemainingLife();
   void drawScore();
   
};

#endif

