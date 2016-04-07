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
#include "Projectile.h"
#include "Laser.h"
#include "Action.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <memory>

struct Point;
struct Vector;
class Sprite;
class Input;

class Player : public Updateable {
  public:
   Point centre;        // ship position
   ALLEGRO_COLOR color; // ship color
   Vector speed;        // movement speed in any direction

   bool dead;           // signals Player object has been killed
   Vector projSpeed;    // speed of projectiles from Player object
   int lives;           // lives remaining of Player object before destroyed
   int speed_modifier;  // affects speed of Player object
   int size;            // ship size in pixels
   int row;
   int col;

   /**
    * @constructor
    */
   Player(Point p, ALLEGRO_COLOR c);

   /**
    * @destructor
    */
   ~Player();

   /**
    * @fn hit(...)
    * @brief 
    * @param 
    */
   void hit(int);

   
   /**
    * @fn draw(...)
    * @brief
    * @param
    */
   void draw(std::shared_ptr<Sprite>);

   
   /**
    * @fn update(...)
    * @brief
    * @param
    */
   void update(double);

   
   /**
    * @fn input(...)
    * @brief
    * @param
    */
   act::action input(ALLEGRO_KEYBOARD_STATE&);

  private:
   // HELPER FUNCTIONS 
   void selectShipAnimation();
   void checkBoundary();
   void drawRemainingLife();
   
};

#endif

